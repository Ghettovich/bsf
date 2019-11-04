#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <incl/domain/arduino.h>
#include "incl/data/dbmanager.h"

DbManager::DbManager(const QString &path) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    qDebug("%s", qUtf8Printable("db manager constructor called"));
    qDebug("path = %s", qUtf8Printable(path));
    //QDir dir("./");
    //qDebug() << "dirName " << dir.currentPath();

}

QList<arduino> DbManager::getAllActiveArduino() {
    QList<arduino> arduinos;
    QSqlQueryModel model;
    QSqlQuery query(m_db);

    qDebug("database name: %s", qUtf8Printable(m_db.databaseName()));
    qDebug("default con: %s", qUtf8Printable(m_db.defaultConnection));
    if (m_db.open()) {
        qDebug("%s", qUtf8Printable("db is open"));

        if (query.exec("SELECT * FROM arduino")) {
            while (query.next()) {
                arduino a;
                a.desc = query.value("description").toString();
                a.id = query.value("id").toInt();
                a.ipAddress = query.value("ipaddress").toString();
                a.name = query.value("name").toString();
                a.port = query.value("port").toInt();
                arduinos.append(a);
                qDebug("id: %s", qUtf8Printable(QStringLiteral("%1").arg(a.id)));
            }
        }
        m_db.close();
    } else {
        qDebug("%s", qUtf8Printable("db NOT open"));
    }

    return arduinos;
}

void DbManager::updateArduino(const arduino& arduinoDevice) {
    qDebug("new name %s", qUtf8Printable(arduinoDevice.name));

    if (m_db.open()) {
        QSqlQuery query;

        query.prepare(
                "UPDATE arduino SET description=:desc, ipaddress=:ipaddress, name=:name, port=:port WHERE id=:id");
        query.bindValue(":desc", arduinoDevice.desc);
        query.bindValue(":ipaddress", arduinoDevice.ipAddress);
        query.bindValue(":name", arduinoDevice.name);
        query.bindValue(":port", arduinoDevice.port);
        query.bindValue(":id", arduinoDevice.id);
        query.exec();
    } else {
        qDebug("new name db is closed!?");
    }
    m_db.close();
}
