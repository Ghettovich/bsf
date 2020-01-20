#include "arduinorepo.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquerymodel.h>

ArduinoRepository::ArduinoRepository() {
}

QList<Arduino> ArduinoRepository::getAllActiveArduino() {
    QString queryString = "SELECT id, name, ipaddress, port, description FROM arduino";
    QList<Arduino> arduinoList;

    try {
        QSqlDatabase db;
        BsfDbconfig dbConfig = BsfDbconfig();

        if (!QSqlDatabase::contains(dbConfig.defaultConnection)) {
            db = QSqlDatabase::addDatabase(dbConfig.database, dbConfig.defaultConnection);
            qDebug("added database");
        } else {
            db = QSqlDatabase::addDatabase(dbConfig.database);
        }

        db.setDatabaseName(dbConfig.databaseName);
        QSqlQuery query(db);

        query.prepare(queryString);
        query.exec();

        while (query.next()) {
            Arduino a;
            a.desc = query.value("description").toString();
            a.id = query.value("id").toInt();
            a.ipAddress = query.value("ipaddress").toString();
            a.name = query.value("name").toString();
            a.port = query.value("port").toInt();
            arduinoList.append(a);
            qDebug("id: %s", qUtf8Printable(QStringLiteral("%1").arg(a.id)));
        }

        db.close();
    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }
    return arduinoList;
}

Arduino ArduinoRepository::getArduino(int id) {
    QString queryString = "SELECT id, name, ipaddress, port, description FROM arduino WHERE id =:id";
    Arduino arduino = Arduino();

    try {
        QSqlDatabase db;
        BsfDbconfig dbConfig = BsfDbconfig();

        if (!QSqlDatabase::contains(dbConfig.defaultConnection)) {
            db = QSqlDatabase::addDatabase(dbConfig.database, dbConfig.defaultConnection);
            qDebug("added database");
        } else {
            db = QSqlDatabase::addDatabase(dbConfig.database);
        }

        db.setDatabaseName(dbConfig.databaseName);
        QSqlQuery query(db);

        query.prepare(queryString);
        query.bindValue(":id", id);
        query.exec();

        if (query.first()) {
            arduino.id = query.value("id").toInt();
            arduino.name = query.value("name").toString();
            arduino.ipAddress = query.value("ipaddress").toString();
            arduino.port = query.value("port").toInt();
            arduino.desc = query.value("description").toString();
        }

        db.close();

    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return arduino;
}

void ArduinoRepository::updateArduino(const Arduino &arduinoDevice) {
    QString queryString = "UPDATE arduino SET description=:desc, ipaddress=:ipaddress, name=:name, port=:port WHERE id=:id";

    try {
        QSqlDatabase db;
        BsfDbconfig dbConfig = BsfDbconfig();

        if (!QSqlDatabase::contains(dbConfig.defaultConnection)) {
            db = QSqlDatabase::addDatabase(dbConfig.database, dbConfig.defaultConnection);
            qDebug("added database");
        } else {
            db = QSqlDatabase::addDatabase(dbConfig.database);
        }

        QSqlQuery query(db);

        query.prepare(queryString);
        query.bindValue(":desc", arduinoDevice.desc);
        query.bindValue(":ipaddress", arduinoDevice.ipAddress);
        query.bindValue(":name", arduinoDevice.name);
        query.bindValue(":port", arduinoDevice.port);
        query.bindValue(":id", arduinoDevice.id);

        if (query.exec()) {
            qDebug("executed update");
            db.close();
        }
    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }
}
