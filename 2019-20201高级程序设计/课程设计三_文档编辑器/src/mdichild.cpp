#include "mdichild.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>
#include <QPushButton>

MdiChild::MdiChild(QWidget *parent) : QTextEdit(parent)
{
    //在子窗口关闭时，销毁这个类的对象
    setAttribute(Qt::WA_DeleteOnClose);
    isUnsaved_flag=true;
}

void MdiChild::newFile()
{
    //设置窗口编号，因为窗口一直保存，所以需要使用静态变量
    static int windowNumber = 1;

    //新建的文档没有被保存过
    isUnsaved_flag= true;

    //将当前文件命名为:未命名文档加窗口编号，窗口编号先使用再加1
    curFile=tr("untitled%1.txt").arg(windowNumber++);

    //设置窗口标题，使用[*]可以在文档更改后，显示未保存
    setWindowTitle(curFile + "[*]");

    //当文档内容被更改时，发射contentsChanged()信号。执行documentWasModified()槽函数，在标题栏上显示‘*’
    connect(document(),SIGNAL(contentsChanged()),this,SLOT(documentWasModified()));

}

// 文档被更改时，窗口显示更改状态标志
void MdiChild::documentWasModified()
{
    // 根据文档的isModified()函数的返回值，判断我们编辑器内容是否被更改了
    // 如果被更改了，参数为true，则setWindowModified()就会在设置了[*]号的地方显示“*”号
    setWindowModified(document()->isModified()); //setWindowModified为库函数

}

// 加载文件
bool MdiChild::loadFile(const QString &filePath)
{
    // 新建QFile对象
    QFile file(filePath);

    // 只读方式打开文件，出错则打开消息提示对话框，并返回false
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        // %1和%2分别可以被后面的arg()中的fileName和file.errorString()代替
        QMessageBox::warning(this, tr("多文档编辑器"),
                             tr("无法读取文件 %1:\n%2.")
                             .arg(filePath).arg(file.errorString()));
        return false;
    }

    // 新建文本流对象
    QTextStream in(&file);

    // 设置鼠标状态为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // 读取文件的全部文本内容，并添加到编辑器中
    setPlainText(in.readAll());

    // 恢复鼠标状态
    QApplication::restoreOverrideCursor();

    // 保存当前文件路径
    setCurrentFile(filePath);

    // 文档的“内容改变”信号，连接到“文档改变槽”，即当文档内容改变，则标题栏出现'*'
    connect(document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));
    return true;
}

// 设置当前文件，将加载文件的路径保存到filepath中
void MdiChild::setCurrentFile(const QString &filePath)
{

    curFile = QFileInfo(filePath).canonicalFilePath();        //去除路径中的符号链接，".",".."
    isUnsaved_flag = false;       //文件已保存
    document()->setModified(false);
    setWindowModified(false);      //窗口不显示被更改标志[*]
    setWindowTitle(getFileNameFromPath()+ "[*]");  //设置窗口标题
}

// 从文件中提取文件名
QString MdiChild::getFileNameFromPath()
{
    return QFileInfo(curFile).fileName();   //从文件路径中提取文件名
}

//保存操作
bool MdiChild::save()
{
    if(isUnsaved_flag)
    {
        return saveAs();     //如果文件未保存，则执行另存为操作
    }
    else
    {
        return saveFile(curFile);  //否则直接保存文件
    }
}

//另存为操作
bool MdiChild::saveAs()
{
    // 获取文件路径，如果为空，返回false
    QString filepath = QFileDialog::getSaveFileName(this,tr("Save_As"),curFile);
    if(filepath.isEmpty())
        return false;
    return saveFile(filepath);  //否则保存文件
}


//保存文件： 本质是根据文件属性，打开硬盘文件，然后写入文档数据
bool MdiChild::saveFile(const QString& filePath)
{
    QFile file(filePath);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,tr("多文档管理器"),
                             tr("无法写入文件 %1:\n%2.").arg(filePath).arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText(); // 以纯文本文件写入
    QApplication::restoreOverrideCursor();
    setCurrentFile(filePath);

    return true;
}


// 关闭事件
void MdiChild::closeEvent(QCloseEvent *event)
{
    if(maybeSave()){
        event->accept();   //如果文件已经保存，直接关闭窗口
    }
    else{
        event->ignore();   //忽视该案件
    }
}

bool MdiChild::maybeSave()
{
    //如果文档被更改过，弹出警告框，让用户选择
    if(document()->isModified())
    {
        QMessageBox box;
        box.setWindowTitle(tr("多文档编辑器"));
        box.setText(tr("是否保存对“%1”的更改？")
                    .arg(getFileNameFromPath()));
        box.setIcon(QMessageBox::Warning);

        // 添加按钮，QMessageBox::YesRole可以表明按钮的行为
        QPushButton *yesBtn = box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
        box.addButton(tr("否(&N)"),QMessageBox::NoRole);

        QPushButton* cancelBtn = box.addButton(tr("取消"),QMessageBox::RejectRole);

        box.exec(); //弹出对话框，让用户选择是否保存修改，或者取消关闭操作
        if(box.clickedButton() == yesBtn)  //如果用户选择是，则返回保存操作的结果
            return save();
        else if(box.clickedButton() == cancelBtn) //如果选择取消，则返回false
            return false;
    }
    return true;
}



