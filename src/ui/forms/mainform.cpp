#include "mainform.h"
#include <main/mainwindow.h>

MainForm::MainForm() {
    parent = new QWidget;
    auto mainWindow = new MainWindow(parent);

    mainWindow->show();
}
