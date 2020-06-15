#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MdiChild;
class QMdiSubWindow;
class QSignalMapper;  //前置类声明

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_File_triggered();
    void on_actionOpen_FIle_triggered();
    void updateMenus(); //更新菜单
    void updateWindowMenu();    // 更新窗口菜单
    MdiChild *createMdiChild(); //创建子窗口
    void setActiveSubWindow(QWidget *window);  //设置活动子窗口
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionClose_O_triggered();
    void on_actionClose_All_A_triggered();
    void on_actionNext_triggered();
    void on_actionPrev_triggered();

private:
    QAction *actionSeparator; //分隔符
    QSignalMapper *windowMapper; //信号映射器
    MdiChild *activeMdiChild(); //活动窗口
    QMdiSubWindow *findMdiChild(const QString &filePath); // 查找子窗口
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
