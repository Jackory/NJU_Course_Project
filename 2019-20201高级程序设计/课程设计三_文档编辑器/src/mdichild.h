#ifndef MDICHILD_H
#define MDICHILD_H

#include <QObject>
#include <QWidget>
#include<QTextEdit>

class MdiChild : public QTextEdit
{
    Q_OBJECT
private:
    bool maybeSave();                       // 判断是否需要保存
    void setCurrentFile(const QString &filePath);  // 设置当前文件

    QString curFile; // 保存新建文件时自动产生的当前文件路径（名称）
    bool isUnsaved_flag; //该标志位判断文件是否为“未保存状态”，若是，则打开文件对话框执行“另存为”操作，否则直接保存

protected:
    void closeEvent(QCloseEvent *event);    // 关闭事件

public:
    explicit MdiChild(QWidget *parent = nullptr);
    void newFile(); // 新建文件
    bool loadFile(const QString &filePath); // 加载文件
    bool save(); // 保存操作
    bool saveAs(); // 另存为操作
    bool saveFile(const QString &filePath); // 保存文件
    QString getFileNameFromPath(); // 从文件路径中提取出文件名
    QString getCurFileName() { return curFile; } // 获得返回的当前文件名称（路径）

signals:

public slots:
    void documentWasModified(); //文档被更改时，窗口显示更改状态标志
};

#endif // MDICHILD_H
