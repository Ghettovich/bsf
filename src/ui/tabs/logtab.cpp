#include "logtab.h"
#include <QtWidgets/QHBoxLayout>
#include <QHeaderView>
#include <QDateTime>
#include <service/logservice.h>

LogTab::LogTab(QTabWidget *parent)
        : QWidget(parent) {
    tableViewBsfLogs = new QTableWidget(this);
    bsfLogList = new QList<BsfLog>;
    bsfLogList = BsfLogService::getBsfLogs();
    createTableView();
}

void LogTab::createTableView() {
    auto *vbox = new QVBoxLayout;
    auto headers = QStringList() << "Datum Tijd" << "Soort" << "Bericht";
    tableViewBsfLogs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableViewBsfLogs->setShowGrid(true);
    tableViewBsfLogs->setColumnCount(headers.size());
    tableViewBsfLogs->setHorizontalHeaderLabels(headers);
    tableViewBsfLogs->showMaximized();

    for (int i = 0; i < bsfLogList->size(); ++i) {
        tableViewBsfLogs->insertRow(i);
        QDateTime dateTimeString = QDateTime::fromSecsSinceEpoch(bsfLogList->at(i).logDateTime);
        tableViewBsfLogs->setItem(i, 0, new QTableWidgetItem(dateTimeString.toString("dd.MM - hh:mm")));
        tableViewBsfLogs->setItem(i, 1, new QTableWidgetItem(convertIODeviceTypeToString(bsfLogList->at(i).logType)));
        tableViewBsfLogs->setItem(i, 2, new QTableWidgetItem(bsfLogList->at(i).log));
    }
    QHeaderView *headerView = tableViewBsfLogs->horizontalHeader();
    headerView->setStretchLastSection(true);
    qDebug("log list size = %s", qUtf8Printable(QString::number(bsfLogList->size())));
    vbox->addWidget(tableViewBsfLogs);
    vbox->setSizeConstraint(QLayout::SetMaximumSize);
    setLayout(vbox);
}

QString LogTab::convertIODeviceTypeToString(int _ioDeviceType) {
    switch (_ioDeviceType) {
        case LogSeverity::ERROR :
            return logTypes.at(0);
        case LogSeverity::WARNING :
            return logTypes.at(1);
        case LogSeverity::INFO :
            return logTypes.at(2);
        default:
            return QString("");
    }
}

