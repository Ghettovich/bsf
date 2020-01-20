
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
                IODeviceType ioDeviceType = IODeviceType(query.value("id").toInt());
                ioDeviceType.setType(query.value("type").toString());
                ioDeviceTypeList.append(ioDeviceType);
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return ioDeviceTypeList;
}

IODeviceType IODeviceRepository::getIODeviceType(int ioDeviceTypeId) {
    QString queryString = "SELECT  id, type, description "
                          "FROM io_device_type "
                          "WHERE id =:id";

    try {
        QSqlQuery query = QSqlQuery(getQSqlDatabase());
        query.prepare(queryString);
        query.bindValue(":id", ioDeviceTypeId);

        if(query.first()) {
            IODeviceType ioDeviceType = IODeviceType(query.value("id").toInt());
            ioDeviceType.setType(query.value("type").toString());
            ioDeviceType.setDescription(query.value("description").toString());
            return ioDeviceType;
        }

        getQSqlDatabase().close();
    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return IODeviceType(0);
}

QList<IODevice> IODeviceRepository::getArduinoIODeviceList(int arduinoId, int ioDeviceType) {
    qDebug("%s", qUtf8Printable("got call to io device list..."));
    QList<IODevice> ioDeviceList;
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
                IODevice ioDevice = IODevice(query.value("io_id").toInt());
                ioDevice.setDescription(query.value("io_desc").toString());
                // Arduino properties
                Arduino arduino = Arduino();
                arduino.desc = query.value("ard_desc").toString();
                arduino.id = query.value("arduino_id").toInt();
                arduino.ipAddress = query.value("ipaddress").toString();
                arduino.name = query.value("name").toString();
                arduino.port = query.value("port").toInt();
                ioDevice.setArduino(arduino);
                // IODeviceType properties
                IODeviceType type = IODeviceType(query.value("type_id").toInt());
                ioDevice.setIoDeviceType(type);
                // Action properties
                Action action = Action(query.value("action_id").toInt());
                action.setCode(query.value("code").toString());
                action.setUrl(query.value("url").toString());
                action.setDescription(query.value("act_desc").toString());
                ioDevice.setAction(action);
                // ADD TO LIST
                ioDeviceList.append(ioDevice);
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return ioDeviceList;
}

QList<IODevice> IODeviceRepository::getArduinoIODeviceList(int arduinoId) {
    QString queryString = "SELECT io.id AS io_id, io.arduino_id, io.type_id, io.action_id, io.description AS io_desc, ard.description AS ard_desc, ard.ipaddress, ard.name, ard.port, act.code, act.url, act.description AS act_desc "
                          "FROM io_device io "
                          "INNER JOIN arduino ard ON ard.id = io.arduino_id "
                          "INNER JOIN action act ON act.id = io.action_id "
                          "WHERE io.arduino_id =:arduino_id "
                          "ORDER BY io.action_id";
    QList<IODevice> ioDeviceList;

    try {
        QSqlQuery query(getQSqlDatabase());
        query.prepare(queryString);
        query.bindValue(":arduino_id", arduinoId);
        qDebug("%s", qUtf8Printable("prepared and binded query..."));

        if (query.exec()) {

            while (query.next()) {
                IODevice ioDevice = IODevice(query.value("io_id").toInt());
                ioDevice.setDescription(query.value("io_desc").toString());
                // Arduino properties
                Arduino arduino = Arduino();
                arduino.desc = query.value("ard_desc").toString();
                arduino.id = query.value("arduino_id").toInt();
                arduino.ipAddress = query.value("ipaddress").toString();
                arduino.name = query.value("name").toString();
                arduino.port = query.value("port").toInt();
                ioDevice.setArduino(arduino);
                // IODeviceType properties
                IODeviceType type = IODeviceType(query.value("type_id").toInt());
                ioDevice.setIoDeviceType(type);
                // Action properties
                Action action = Action(query.value("action_id").toInt());
                action.setCode(query.value("code").toString());
                action.setUrl(query.value("url").toString());
                action.setDescription(query.value("act_desc").toString());
                ioDevice.setAction(action);
                // ADD TO LIST
                ioDeviceList.append(ioDevice);
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return ioDeviceList;
}

QList<WeightCensor> IODeviceRepository::getArduinoWeightSensorList(int arduinoId) {
    qDebug("%s", qUtf8Printable("got call to get arduino weight sensor list..."));
    QList<WeightCensor> ioDeviceList;
    QString queryString = "SELECT io.id AS io_id, io.arduino_id, io.type_id, io.action_id, io.description AS io_desc, ard.description AS ard_desc, ard.ipaddress, ard.name, ard.port, act.code, act.url, act.description AS act_desc "
                          "FROM io_device io "
                          "INNER JOIN arduino ard ON ard.id = io.arduino_id "
                          "INNER JOIN action act ON act.id = io.action_id "
                          "WHERE io.type_id =:type_id AND io.arduino_id =:arduino_id "
                          "ORDER BY io.action_id";

    try {
        QSqlQuery query(getQSqlDatabase());
        query.prepare(queryString);

        query.bindValue(":type_id", IODeviceType::WEIGHTSENSOR);
        query.bindValue(":arduino_id", arduinoId);

        qDebug("%s", qUtf8Printable("prepared and binded query..."));

        if (query.exec()) {
            while (query.next()) {
                WeightCensor weightSensorDevice = WeightCensor(query.value("io_id").toInt());
                weightSensorDevice.setDescription(query.value("io_desc").toString());
                // Arduino properties
                Arduino arduino = Arduino();
                arduino.desc = query.value("ard_desc").toString();
                arduino.id = query.value("arduino_id").toInt();
                arduino.ipAddress = query.value("ipaddress").toString();
                arduino.name = query.value("name").toString();
                arduino.port = query.value("port").toInt();
                weightSensorDevice.setArduino(arduino);
                // IODeviceType properties
                IODeviceType type = IODeviceType(query.value("type_id").toInt());
                weightSensorDevice.setIoDeviceType(type);
                // Action properties
                Action action = Action(query.value("action_id").toInt());
                action.setCode(query.value("code").toString());
                action.setUrl(query.value("url").toString());
                action.setDescription(query.value("act_desc").toString());
                weightSensorDevice.setAction(action);
                // ADD TO LIST
                ioDeviceList.append(weightSensorDevice);
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return ioDeviceList;
}

QSqlDatabase IODeviceRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig.defaultConnection);
}
