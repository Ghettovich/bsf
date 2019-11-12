#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include "incl/repo/arduinorepo.h"
#include <incl/log/bsflog.h>

ArduinoRepository::ArduinoRepository() {
    bsfDbConfig = new BsfDbconfig;
    qDebug("%s", qUtf8Printable(bsfDbConfig->getDefaultConnection()));
    qDebug("%s", qUtf8Printable(bsfDbConfig->getDatabaseName()));
    qDebug("%s", qUtf8Printable(bsfDbConfig->getDatabase()));
    if(!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig->getDatabase(), bsfDbConfig->getDefaultConnection());
        bsfDb.setDatabaseName(bsfDbConfig->getDatabaseName());
    }
}

QList<Arduino> ArduinoRepository::getAllActiveArduino() {
    QList<Arduino> arduinos;

    try {
        QSqlQuery query(getQSqlDatabase());

        if (query.exec("SELECT * FROM arduino")) {
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
    } catch (std::exception & e) {
        BsfLogger::addLog(e.what(), LogSeverity::ERROR);
    }

    return arduinos;
}

void ArduinoRepository::updateArduino(const Arduino &arduinoDevice) {
    try {
        QSqlQuery query(getQSqlDatabase());

        query.prepare(
                "UPDATE arduino SET description=:desc, ipaddress=:ipaddress, name=:name, port=:port WHERE id=:id");
        query.bindValue(":desc", arduinoDevice.desc);
        query.bindValue(":ipaddress", arduinoDevice.ipAddress);
        query.bindValue(":name", arduinoDevice.name);
        query.bindValue(":port", arduinoDevice.port);
        query.bindValue(":id", arduinoDevice.id);

        if (query.exec()) {
            qDebug("executed update");
            getQSqlDatabase().close();
        }
    } catch (std::exception & e) {
        BsfLogger::addLog(e.what(), LogSeverity::ERROR);
    }
}

QSqlDatabase ArduinoRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}
