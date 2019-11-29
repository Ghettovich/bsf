#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>
#include <incl/log/bsflog.h>
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

IODeviceType *IODeviceRepository::getIODeviceType(int ioDeviceTypeId) {
    QString queryString = "SELECT  id, type, description "
                          "FROM io_device_type "
                          "WHERE id =:id";
    auto *ioDeviceType = new IODeviceType();

    try {
        QSqlQuery query = QSqlQuery(getQSqlDatabase());
        query.prepare(queryString);
        query.bindValue(":id", ioDeviceTypeId);

        if(query.first()) {
            ioDeviceType->id = query.value("id").toInt();
            ioDeviceType->type = query.value("type").toInt();
            ioDeviceType->description = query.value("description").toInt();
        }

        getQSqlDatabase().close();
    } catch (std::exception &e) {
        BsfLogger::addLog(e.what(), LogSeverity::ERROR);
    }

    return ioDeviceType;
}

QList<IODevice *> IODeviceRepository::getArduinoIODeviceList(int arduino_id, int ioDeviceType) {
    qDebug("%s", qUtf8Printable("got call to io device list..."));
    QList<IODevice *> ioDeviceList;
    QString queryString = "SELECT io.id, ard.description, io.arduino_id, io.type_id, ard.ipaddress, ard.name, ard.port, io.action_id, act.code, act.description, io.description "
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

        qDebug("%s", qUtf8Printable("prepared and binded query..."));

        if (query.exec()) {

            while (query.next()) {
                qDebug("%s", qUtf8Printable("got io device"));
                IODevice *ioDevice = new IODevice;
                ioDevice->id = query.value(0).toInt();
                ioDevice->arduino.desc = query.value(1).toString();
                ioDevice->arduino.id = query.value(2).toInt();
                ioDevice->ioDeviceType.id = query.value(3).toInt();
                ioDevice->arduino.ipAddress = query.value(4).toString();
                ioDevice->arduino.name = query.value(5).toString();
                ioDevice->arduino.port = query.value(6).toInt();
                ioDevice->action.id = query.value(7).toInt();
                ioDevice->action.code = query.value(8).toString();
                ioDevice->action.description = query.value(9).toString();
                ioDevice->description = query.value(10).toString();
                ioDeviceList.append(ioDevice);
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        qDebug(e.what());
    }

    return ioDeviceList;
}

QSqlDatabase IODeviceRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}
