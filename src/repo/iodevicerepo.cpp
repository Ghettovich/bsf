
#include "iodevicerepo.h"
#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>


IODeviceRepository::IODeviceRepository() {
    //bsfDbConfig = new BsfDbconfig;
    // ToDo: verify if dereference pointer is necessary
    if (!QSqlDatabase::contains()) {
        auto bsfDb = QSqlDatabase::addDatabase(bsfDbConfig.database, bsfDbConfig.defaultConnection);
        bsfDb.setDatabaseName(bsfDbConfig.databaseName);
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
            ioDeviceType->type = query.value("type").toString();
            ioDeviceType->description = query.value("description").toString();
        }

        getQSqlDatabase().close();
    } catch (std::exception &e) {
        qDebug(e.what());
    }

    return ioDeviceType;
}

QList<IODevice *> IODeviceRepository::getArduinoIODeviceList(int arduinoId, int ioDeviceType) {
    qDebug("%s", qUtf8Printable("got call to io device list..."));
    QList<IODevice *> ioDeviceList;
    QString queryString = "SELECT io.id AS io_id, io.arduino_id, io.type_id, io.action_id, io.description AS io_desc, ard.description AS ard_desc, ard.ipaddress, ard.name, ard.port, act.code, act.url, act.description AS act_desc "
                          "FROM io_device io "
                          "INNER JOIN arduino ard ON ard.id = io.arduino_id "
                          "INNER JOIN action act ON act.id = io.action_id "
                          "WHERE io.type_id =:type_id AND io.arduino_id =:arduino_id "
                          "ORDER BY io.action_id";

    try {
        QSqlQuery query(getQSqlDatabase());
        query.prepare(queryString);

        query.bindValue(":type_id", ioDeviceType);
        query.bindValue(":arduino_id", arduinoId);

        qDebug("%s", qUtf8Printable("prepared and binded query..."));

        if (query.exec()) {
            while (query.next()) {
                auto *ioDevice = new IODevice(query.value("io_id").toInt());
                ioDevice->setDescription(query.value("io_desc").toString());
                // Arduino properties
                Arduino arduino = Arduino();
                arduino.desc = query.value("ard_desc").toString();
                arduino.id = query.value("arduino_id").toInt();
                arduino.ipAddress = query.value("ipaddress").toString();
                arduino.name = query.value("name").toString();
                arduino.port = query.value("port").toInt();
                ioDevice->setArduino(arduino);
                // IODeviceType properties
                IODeviceType type = IODeviceType();
                type.id = query.value("type_id").toInt();
                ioDevice->setIoDeviceType(type);
                // Action properties
                Action action = Action();
                action.id = query.value("action_id").toInt();
                action.code = query.value("code").toString();
                action.url = query.value("url").toString();
                action.description = query.value("act_desc").toString();
                ioDevice->setAction(action);
                // ADD TO LIST
                ioDeviceList.append(ioDevice);
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        qDebug(e.what());
    }

    return ioDeviceList;
}

QList<IODevice *> IODeviceRepository::getArduinoIODeviceList(int arduinoId) {
    QString queryString = "SELECT io.id AS io_id, io.arduino_id, io.type_id, io.action_id, io.description AS io_desc, ard.description AS ard_desc, ard.ipaddress, ard.name, ard.port, act.code, act.url, act.description AS act_desc "
                          "FROM io_device io "
                          "INNER JOIN arduino ard ON ard.id = io.arduino_id "
                          "INNER JOIN action act ON act.id = io.action_id "
                          "WHERE io.arduino_id =:arduino_id "
                          "ORDER BY io.action_id";
    QList<IODevice *> ioDeviceList;

    try {
        QSqlQuery query(getQSqlDatabase());
        query.prepare(queryString);
        query.bindValue(":arduino_id", arduinoId);
        qDebug("%s", qUtf8Printable("prepared and binded query..."));

        if (query.exec()) {

            while (query.next()) {
                auto *ioDevice = new IODevice(query.value("io_id").toInt());
                ioDevice->setDescription(query.value("io_desc").toString());
                // Arduino properties
                Arduino arduino = Arduino();
                arduino.desc = query.value("ard_desc").toString();
                arduino.id = query.value("arduino_id").toInt();
                arduino.ipAddress = query.value("ipaddress").toString();
                arduino.name = query.value("name").toString();
                arduino.port = query.value("port").toInt();
                ioDevice->setArduino(arduino);
                // IODeviceType properties
                IODeviceType type = IODeviceType();
                type.id = query.value("type_id").toInt();
                ioDevice->setIoDeviceType(type);
                // Action properties
                Action action = Action();
                action.id = query.value("action_id").toInt();
                action.code = query.value("code").toString();
                action.url = query.value("url").toString();
                action.description = query.value("act_desc").toString();
                ioDevice->setAction(action);
                // ADD TO LIST
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
    return QSqlDatabase::database(bsfDbConfig.defaultConnection);
}

QList<WeightCensor *> IODeviceRepository::getArduinoWeightSensorList(int arduinoId) {

    qDebug("%s", qUtf8Printable("got call to get arduino weight sensor list..."));
    QList<WeightCensor *> ioDeviceList;
    QString queryString = "SELECT io.id AS io_id, io.arduino_id, io.type_id, io.action_id, io.description AS io_desc, ard.description AS ard_desc, ard.ipaddress, ard.name, ard.port, act.code, act.url, act.description AS act_desc "
                          "FROM io_device io "
                          "INNER JOIN arduino ard ON ard.id = io.arduino_id "
                          "INNER JOIN action act ON act.id = io.action_id "
                          "WHERE io.type_id =:type_id AND io.arduino_id =:arduino_id "
                          "ORDER BY io.action_id";

    try {
        QSqlQuery query(getQSqlDatabase());
        query.prepare(queryString);

        query.bindValue(":type_id", WEIGHTSENSOR);
        query.bindValue(":arduino_id", arduinoId);

        qDebug("%s", qUtf8Printable("prepared and binded query..."));

        if (query.exec()) {
            while (query.next()) {
                auto *ioDevice = new WeightCensor(query.value("io_id").toInt());
                ioDevice->setDescription(query.value("io_desc").toString());
                // Arduino properties
                Arduino arduino = Arduino();
                arduino.desc = query.value("ard_desc").toString();
                arduino.id = query.value("arduino_id").toInt();
                arduino.ipAddress = query.value("ipaddress").toString();
                arduino.name = query.value("name").toString();
                arduino.port = query.value("port").toInt();
                ioDevice->setArduino(arduino);
                // IODeviceType properties
                IODeviceType type = IODeviceType();
                type.id = query.value("type_id").toInt();
                ioDevice->setIoDeviceType(type);
                // Action properties
                Action action = Action();
                action.id = query.value("action_id").toInt();
                action.code = query.value("code").toString();
                action.url = query.value("url").toString();
                action.description = query.value("act_desc").toString();
                ioDevice->setAction(action);
                // ADD TO LIST
                ioDeviceList.append(ioDevice);
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        qDebug(e.what());
    }

    return ioDeviceList;
}
