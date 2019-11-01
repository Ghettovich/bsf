#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <ui_mainwindow.h>
#include "maintabbarwidget.h"
#include "server.h"
#include "headers/models/logtablemodel.h"

class QAction;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:

private slots:
    void newFile();
    void open();
    void save();
signals:

private:
    void createMainTabBar();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    const QString defaultMainStatusBarMsg = "Ready";

    // Menu
    QMenu *fileMenu;
    QMenu *helpMenu;
    // Toolbar
    QToolBar *fileToolBar;

    // StatusBar
    QStatusBar *mainStatusBar;
    // Actions
    QAction *updateStatusBar;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *aboutQtAct;

    QWidget *tab1;
    QWidget *mainTabBar;
    QTabWidget *bsfTabWidget;

    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
