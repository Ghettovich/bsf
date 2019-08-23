#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
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
    void saveAs();
    void about();        
    void documentWasModified();

signals:

private:
    void createMainTabBar();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    QString strippedName(const QString &fullFileName);
    const QString defaultMainStatusBarMsg = "Ready";

    // Widgets
    MainTabBarWidget *mainTabWidget;

    QPlainTextEdit *textEdit;
    QString curFile;
    // Menu
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    // Toolbar
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    // StatusBar
    QStatusBar *mainStatusBar;
    // Actions
    QAction *updateStatusBar;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif // MAINWINDOW_H
