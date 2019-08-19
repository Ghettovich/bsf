#include "headers/tabs/main/logtab.h"
#include <QHeaderView>
#include <QRegularExpression>
#include <QTableView>
#include <QWidget>
#include <qsortfilterproxymodel.h>

LogTab::LogTab(QTabWidget *parent)
    : QTabWidget(parent),
      logTable(new LogTableModel(this))
{
}

void LogTab::createTableView()
{
    // To Do create columns from constants
    const auto regExp = QRegularExpression(QString("^[%1].*").arg("Logs"),
                                           QRegularExpression::CaseInsensitiveOption);
}
