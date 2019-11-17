#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include "incl/repo/iodevicerepo.h"


IODeviceRepository::IODeviceRepository() {
    bsfDbConfig = new BsfDbconfig;
    if (!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig->getDatabase(), bsfDbConfig->getDefaultConnection());
        bsfDb.setDatabaseName(bsfDbConfig->getDatabaseName());
    }
}

QList<IODeviceType> IODeviceRepository::getArduinoIODeviceTypes(int id) {
    QString queryString = "SELECT io_device_type.id, io_device_type.type FROM io_device_type INNER JOIN io_device ON io_device.type_id = io_device_type.id WHERE io_device.arduino_id =:id GROUP BY io_device_type.id, io_device_type.type";
    QList<IODeviceType> ioDeviceTypeList;

    try {
        QSqlQuery query(getQSqlDatabase());
        query.prepare(queryString);
        query.bindValue(":id", id);

        if (query.exec()) {

            while (query.next()) {
                IODeviceType ioDeviceType;
                ioDeviceType.id = query.value("id").toInt();
                ioDeviceType.type = query.value("type").toString();
                ioDeviceTypeList.append(ioDeviceType);
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        qDebug(e.what());
    }

    return ioDeviceTypeList;
}

QList<IODevice> IODeviceRepository::getArduinoIODeviceList(int arduino_id, int ioDeviceType) {
    QList<IODevice> arduinoIODeviceList;
    QString queryString = "SELECT io.id, ard.description, io.arduino_id, ard.ipaddress, ard.name, ard.port, io.action_id, act.code, act.description "
                    "FROM io_device io "
                    "INNER JOIN arduino ard ON ard.id = io.arduino_id "
                    "INNER JOIN action act ON act.id = io.action_id "
                    "WHERE io.type_id =:type_id AND io.arduino_id =:arduino_id "
                    "ORDER BY io.action_id";

    try {
        QSqlQuery query(getQSqlDatabase());
        query.prepare(queryString);

        query.bindValue(":type_id", ioDeviceType);
        query.bindValue(":arduino_id", arduino_id);

        if (query.exec()) {

            while (query.next()) {
                IODevice aa;
                aa.id = query.value("id").toInt();
                aa.arduino.desc = query.value("description").toString();
                aa.arduino.id = query.value("arduino_id").toInt();
                aa.arduino.ipAddress = query.value("ipaddress").toString();
                aa.arduino.name = query.value("name").toString();
                aa.arduino.port = query.value("port").toInt();
                aa.action.id = query.value("action_id").toInt();
                aa.action.code = query.value("code").toString();
                aa.action.description = query.value("description").toString();
                arduinoIODeviceList.append(aa);
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        qDebug(e.what());
    }

    return arduinoIODeviceList;
}

QSqlDatabase IODeviceRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}
