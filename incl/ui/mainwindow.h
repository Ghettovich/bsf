#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

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

private:
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

#endif // MAINWINDOW_H
