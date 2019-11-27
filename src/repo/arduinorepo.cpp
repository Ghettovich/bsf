#include "incl/repo/arduinorepo.h"
#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include <incl/log/bsflog.h>

ArduinoRepository::ArduinoRepository() {
    bsfDbConfig = new BsfDbconfig;
    if (!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig->getDatabase(), bsfDbConfig->getDefaultConnection());
        bsfDb.setDatabaseName(bsfDbConfig->getDatabaseName());
    }
}

QList<Arduino> ArduinoRepository::getAllActiveArduino() {
    QString queryString = "SELECT id, name, ipaddress, port, description FROM arduino";
    QList<Arduino> arduinos;

    try {
        QSqlQuery query(getQSqlDatabase());

        if (query.exec(queryString)) {
            while (query.next()) {
                Arduino a;
                a.desc = query.value("description").toString();
                a.id = query.value("id").toInt();
                a.ipAddress = query.value("ipaddress").toString();
                a.name = query.value("name").toString();
                a.port = query.value("port").toInt();
                arduinos.append(a);
                qDebug("id: %s", qUtf8Printable(QStringLiteral("%1").arg(a.id)));
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        BsfLogger::addLog(e.what(), LogSeverity::ERROR);
    }

    return arduinos;
}

Arduino ArduinoRepository::getArduino(int id) {
    QString queryString = "SELECT id, name, ipaddress, port, description FROM arduino WHERE id =:id";
    Arduino arduino = Arduino();

    try {
        QSqlQuery query(getQSqlDatabase());
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
        getQSqlDatabase().close();

    } catch (std::exception &e) {
        BsfLogger::addLog(e.what(), LogSeverity::ERROR);
    }

    return arduino;
}

void ArduinoRepository::updateArduino(const Arduino &arduinoDevice) {
    QString queryString = "UPDATE arduino SET description=:desc, ipaddress=:ipaddress, name=:name, port=:port WHERE id=:id";

    try {
        QSqlQuery query(getQSqlDatabase());

        query.prepare(queryString);
        query.bindValue(":desc", arduinoDevice.desc);
        query.bindValue(":ipaddress", arduinoDevice.ipAddress);
        query.bindValue(":name", arduinoDevice.name);
        query.bindValue(":port", arduinoDevice.port);
        query.bindValue(":id", arduinoDevice.id);

        if (query.exec()) {
            qDebug("executed update");
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        BsfLogger::addLog(e.what(), LogSeverity::ERROR);
    }
}

QSqlDatabase ArduinoRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}
