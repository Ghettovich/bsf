#ifndef BSF_MAINWINDOW_H
#define BSF_MAINWINDOW_H

#include "ui_mainwindow.h"
#include <ui/controller/tab/tabcontroller.h>
#include <QMainWindow>
#include <QToolBar>
#include <QStatusBar>


class QAction;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void onNotifyOperatorWithErrorCode(const QString &errorCode);

private slots:
    void newFile();
    void open();
    void save();

private:
    TabController * tabController = nullptr;
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    const QString defaultMainStatusBarMsg = "Ready";

    // Menu
    QMenu *fileMenu = nullptr;
    QMenu *helpMenu = nullptr;
    // Toolbar
    QToolBar *fileToolBar = nullptr;

    // StatusBar
    QStatusBar *mainStatusBar = nullptr;
    // Actions
    QAction *updateStatusBar = nullptr;
    QAction *newAct = nullptr;
    QAction *openAct = nullptr;
    QAction *saveAct = nullptr;
    QAction *exitAct = nullptr;
    QAction *aboutQtAct = nullptr;
};

#endif // BSF_MAINWINDOW_H
