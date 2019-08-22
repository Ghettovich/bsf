#include "headers/tabs/main/logtab.h"
#include <QAction>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableView>
#include <QWidget>
#include <mainwindow.h>

LogTab::LogTab(QTabWidget *parent)
    : QWidget(parent)
{
    setStatusTip(statusBarMsg);
}
