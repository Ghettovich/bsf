#include "mainwindow.h"
#include <QMessageBox>
#include <QIcon>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    tabController = new TabController(this);
    tabController->createBsfTabs(this);
    setCentralWidget(tabController->getCurrentPage());

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createActions() {
    /* BIND FILE MENU ACTIONS */
    newAct = new QAction( tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);
    menuBar()->addSeparator();

    menuBar()->addSeparator();
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars() {
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->setMovable(false);
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
}

void MainWindow::createStatusBar() {
    mainStatusBar = statusBar();
    mainStatusBar->showMessage(tr("Ready"));
}

/* PUBLIC SLOTS */
void MainWindow::onNotifyOperatorWithErrorCode(const QString &errorCode) {
    mainStatusBar->showMessage(errorCode);
}

/* PRIVATE SLOTS */
void MainWindow::newFile() {

}

void MainWindow::open() {

}

void MainWindow::save() {

}
