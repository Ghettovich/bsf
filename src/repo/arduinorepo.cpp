#include <incl/repo/arduinorepo.h>
#include <QtSql/qsqlquerymodel.h>
#include <QtSql/QSqlQuery>

ArduinoRepository::ArduinoRepository() {
    bsfDbConfig = new BsfDbconfig;
    auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig->getDatabase(), bsfDbConfig->getDefaultConnection());
    bsfDb.setDatabaseName(bsfDbConfig->getDatabaseName());
}

QList<arduino> ArduinoRepository::getAllActiveArduino() {
    QList<arduino> arduinos;
    QSqlQuery query(getQSqlDatabase());

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
    else {
        qDebug("failed to execute getAllActiveArduino");
    }
    return arduinos;
}

void ArduinoRepository::updateArduino(const arduino &arduinoDevice) {
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
    } else {
        qDebug("failed to execute update");
    }
}

QSqlDatabase ArduinoRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}
