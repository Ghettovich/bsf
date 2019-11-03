#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <incl/domain/arduino.h>
#include "incl/data/dbmanager.h"

DbManager::DbManager(const QString &path) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    m_db.open();

    //QDir dir("./");
    //qDebug() << "dirName " << dir.currentPath();
}

QList<arduino> DbManager:: getAllActiveArduino() {
    QList<arduino> arduinos;
    QSqlQueryModel model;

    model.setQuery("SELECT * FROM arduino");

    if(m_db.open()) {
        for (int i = 0; i < model.rowCount(); ++i) {
            arduino a;
            a.desc = model.record(i).value("description").toString();
            a.id = model.record(i).value("id").toInt();
            a.ipAddress = model.record(i).value("ipaddress").toString();
            a.name = model.record(i).value("name").toString();
            a.port = model.record(i).value("port").toInt();
            arduinos.append(a);
        }
    }

    return arduinos;
}
