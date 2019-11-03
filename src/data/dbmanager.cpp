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


QList<ArduinoDevice*> DbManager:: getAllActiveArduino() {
    QList<ArduinoDevice*> arduinos;
    QSqlQueryModel model;

    model.setQuery("SELECT * FROM arduino");

    if(m_db.open()) {
        for (int i = 0; i < model.rowCount(); ++i) {
            ArduinoDevice *arduinoDevice = new ArduinoDevice;

            arduinoDevice->setName(model.record(i).value("name").toString());
            arduinoDevice->setIpAddress(model.record(i).value("ipaddress").toString());
            arduinoDevice->setPort(model.record(i).value("port").toInt());
            arduinoDevice->setDescription(model.record(i).value("description").toString());

            arduinos.append(arduinoDevice);
        }
    }

    return arduinos;
}
