#include "logtab.h"
#include <service/logservice.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtCore/QDateTime>

LogTab::LogTab(QWidget * parent, const Qt::WindowFlags &f) : QWidget(parent, f) {
    tableViewBsfLogs = new QTableWidget(this);
    createTableView();
}

void LogTab::createTableView() {
    BsfLogService logService = BsfLogService();
    QVector<BafaLog> bsfLogList = logService.getBsfLogList();

    auto *vbox = new QVBoxLayout;
    auto headers = QStringList() << "Datum Tijd" << "Soort" << "Bericht";
    tableViewBsfLogs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableViewBsfLogs->setShowGrid(true);
    tableViewBsfLogs->setColumnCount(headers.size());
    tableViewBsfLogs->setHorizontalHeaderLabels(headers);
    tableViewBsfLogs->showMaximized();

    for (int i = 0; i < bsfLogList.size(); ++i) {
        tableViewBsfLogs->insertRow(i);
        QDateTime dateTimeString = QDateTime::fromSecsSinceEpoch(bsfLogList.at(i).getLogDateTime());
        tableViewBsfLogs->setItem(i, 0, new QTableWidgetItem(dateTimeString.toString("dd.MM - hh:mm")));
        tableViewBsfLogs->setItem(i, 1, new QTableWidgetItem(convertIODeviceTypeToString(bsfLogList.at(i).getLogSeverity())));
        tableViewBsfLogs->setItem(i, 2, new QTableWidgetItem(bsfLogList.at(i).getLog()));
    }
    QHeaderView *headerView = tableViewBsfLogs->horizontalHeader();
    headerView->setStretchLastSection(true);
    vbox->addWidget(tableViewBsfLogs);
    vbox->setSizeConstraint(QLayout::SetMaximumSize);
    setLayout(vbox);
}

QString LogTab::convertIODeviceTypeToString(BafaLog::LOG_SEVERITY _severity) {
    switch (_severity) {
        case BafaLog::ERROR :
            return logTypes.at(0);
        case BafaLog::WARNING :
            return logTypes.at(1);
        case BafaLog::INFO :
            return logTypes.at(2);
        default:
            return QString("");
    }
}

