#include "iodevicerepo.h"
#include <data/bsfdatabaseconfig.h>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>

IODeviceRepository::IODeviceRepository() {
}

QVector<IODeviceType> IODeviceRepository::getArduinoIODeviceTypes(int id) {
    QVector<IODeviceType> ioDeviceTypeList = QVector<IODeviceType>();
    QString queryString = "SELECT io_device_type.id, io_device_type.type "
                          "FROM io_device_type INNER JOIN io_device ON io_device.type_id = io_device_type.id "
                          "WHERE io_device.arduino_id =:id "
                          "GROUP BY io_device_type.id, io_device_type.type ";

    try {
        QSqlDatabase db;
        setDefaultDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":id", id);

        query.exec();

        while (query.next()) {
            IODeviceType ioDeviceType = IODeviceType(query.value("id").toInt());
            ioDeviceType.setType(query.value("type").toString());
            ioDeviceType.setIODeviceType(IODeviceType::IO_DEVICE_TYPE(ioDeviceType.getId()));
            ioDeviceTypeList.append(ioDeviceType);
        }

        db.close();
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
        QSqlDatabase db;
        setDefaultDatabase(db);
        QSqlQuery query = QSqlQuery(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":id", ioDeviceTypeId);

        if (query.first()) {
            IODeviceType ioDeviceType = IODeviceType(query.value("id").toInt());
            ioDeviceType.setType(query.value("type").toString());
            ioDeviceType.setDescription(query.value("description").toString());
            ioDeviceType.setIODeviceType(IODeviceType::IO_DEVICE_TYPE(ioDeviceType.getId()));
            return ioDeviceType;
        }

    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return IODeviceType(0);
}

QVector<IODevice> IODeviceRepository::getArduinoIODeviceList(int arduinoId, int ioDeviceTypeId) {
    QVector<IODevice> ioDeviceList;
    QString queryString = "SELECT io.id AS io_id, io.arduino_id, io.type_id, io.action_id, io.description AS io_desc, ard.description AS ard_desc, ard.ipaddress, ard.name, ard.port, act.code, act.url, act.description AS act_desc "
                          "FROM io_device io "
                          "INNER JOIN arduino ard ON ard.id = io.arduino_id "
                          "INNER JOIN action act ON act.id = io.action_id "
                          "WHERE io.type_id =:type_id AND io.arduino_id =:arduino_id "
                          "ORDER BY io.action_id";

    try {
        qDebug("Arduino id = %s \nIODeviceType id = %s",
               qUtf8Printable(QString::number(arduinoId)), qUtf8Printable(QString::number(ioDeviceTypeId)));

        if (ioDeviceTypeId > 0 && arduinoId > 0) {
            QSqlDatabase db;
            setDefaultDatabase(db);
            QSqlQuery query(db);

            db.open();
            query.prepare(queryString);
            query.bindValue(":type_id", ioDeviceTypeId);
            query.bindValue(":arduino_id", arduinoId);

            query.exec();
            while (query.next()) {
                IODevice ioDevice = IODevice(query.value("io_id").toInt());
                ioDevice.setDescription(query.value("io_desc").toString());
                // Arduino properties
                Arduino arduino = Arduino(query.value("arduino_id").toInt());
                arduino.setDesc(query.value("ard_desc").toString());
                arduino.setIpAddress(query.value("ipaddress").toString());
                arduino.setName(query.value("name").toString());
                arduino.setPort(query.value("port").toInt());
                ioDevice.setArduino(arduino);
                // IODeviceType properties
                IODeviceType ioDeviceType = IODeviceType(query.value("type_id").toInt());
                ioDeviceType.setIODeviceType(IODeviceType::IO_DEVICE_TYPE(ioDeviceType.getId()));
                ioDevice.setIoDeviceType(ioDeviceType);
                // Action properties
                Action action = Action(query.value("action_id").toInt());
                action.setCode(query.value("code").toString());
                action.setUrl(query.value("url").toString());
                action.setDescription(query.value("act_desc").toString());
                ioDevice.setAction(action);
                // ADD TO LIST
                ioDeviceList.append(ioDevice);
            }

            db.close();
        }
    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return ioDeviceList;
}

QVector<IODevice> IODeviceRepository::getArduinoIODeviceList(int arduinoId) {
    QVector<IODevice> ioDeviceList;
    QString queryString = "SELECT io.id AS io_id, io.arduino_id, io.type_id, io.action_id, io.description AS io_desc, ard.description AS ard_desc, ard.ipaddress, ard.name, ard.port, act.code, act.url, act.description AS act_desc "
                          "FROM io_device io "
                          "INNER JOIN arduino ard ON ard.id = io.arduino_id "
                          "INNER JOIN action act ON act.id = io.action_id "
                          "WHERE io.arduino_id =:arduino_id "
                          "ORDER BY io.action_id";

    try {

        if (arduinoId > 0) {
            QSqlDatabase db;
            setDefaultDatabase(db);
            QSqlQuery query(db);

            db.open();
            query.prepare(queryString);
            query.bindValue(":arduino_id", arduinoId);
            qDebug("%s", qUtf8Printable("prepared and binded query..."));

            query.exec();
            while (query.next()) {
                IODevice ioDevice = IODevice(query.value("io_id").toInt());
                ioDevice.setDescription(query.value("io_desc").toString());
                // Arduino properties
                Arduino arduino = Arduino(query.value("arduino_id").toInt());
                arduino.setDesc(query.value("ard_desc").toString());
                arduino.setIpAddress(query.value("ipaddress").toString());
                arduino.setName(query.value("name").toString());
                arduino.setPort(query.value("port").toInt());
                ioDevice.setArduino(arduino);
                // IODeviceType properties
                IODeviceType ioDeviceType = IODeviceType(query.value("type_id").toInt());
                ioDeviceType.setIODeviceType(IODeviceType::IO_DEVICE_TYPE(ioDeviceType.getId()));
                ioDevice.setIoDeviceType(ioDeviceType);
                // Action properties
                Action action = Action(query.value("action_id").toInt());
                action.setCode(query.value("code").toString());
                action.setUrl(query.value("url").toString());
                action.setDescription(query.value("act_desc").toString());
                ioDevice.setAction(action);
                // ADD TO LIST
                ioDeviceList.append(ioDevice);
            }

            db.close();
        } else {
            qDebug("Arduino id = %s", qUtf8Printable(QString::number(arduinoId)));
        }

    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return ioDeviceList;
}

QVector<WeightCensor> IODeviceRepository::getArduinoWeightSensorList(int arduinoId) {
    qDebug("%s", qUtf8Printable("got call to get arduino weight sensor list..."));
    QVector<WeightCensor> ioDeviceList;
    QString queryString = "SELECT io.id AS io_id, io.arduino_id, io.type_id, io.action_id, io.description AS io_desc, ard.description AS ard_desc, ard.ipaddress, ard.name, ard.port, act.code, act.url, act.description AS act_desc "
                          "FROM io_device io "
                          "INNER JOIN arduino ard ON ard.id = io.arduino_id "
                          "INNER JOIN action act ON act.id = io.action_id "
                          "WHERE io.type_id =:type_id AND io.arduino_id =:arduino_id "
                          "ORDER BY io.action_id";

    try {
        if (arduinoId > 0) {
            QSqlDatabase db;
            setDefaultDatabase(db);
            QSqlQuery query(db);

            db.open();
            query.prepare(queryString);
            query.bindValue(":type_id", weightSensorTypeId);
            query.bindValue(":arduino_id", arduinoId);
            query.exec();

            qDebug("%s", qUtf8Printable("prepared and binded query..."));

            while (query.next()) {
                WeightCensor weightSensorDevice = WeightCensor(query.value("io_id").toInt());
                weightSensorDevice.setDescription(query.value("io_desc").toString());
                // Arduino properties
                Arduino arduino = Arduino(query.value("arduino_id").toInt());
                arduino.setDesc(query.value("ard_desc").toString());
                arduino.setIpAddress(query.value("ipaddress").toString());
                arduino.setName(query.value("name").toString());
                arduino.setPort(query.value("port").toInt());
                weightSensorDevice.setArduino(arduino);
                // IODeviceType properties
                IODeviceType ioDeviceType = IODeviceType(query.value("type_id").toInt());
                ioDeviceType.setIODeviceType(IODeviceType::IO_DEVICE_TYPE(ioDeviceType.getId()));
                weightSensorDevice.setIoDeviceType(ioDeviceType);
                // Action properties
                Action action = Action(query.value("action_id").toInt());
                action.setCode(query.value("code").toString());
                action.setUrl(query.value("url").toString());
                action.setDescription(query.value("act_desc").toString());
                weightSensorDevice.setAction(action);
                // ADD TO LIST
                ioDeviceList.append(weightSensorDevice);
            }

            db.close();

        } else {
            qDebug("arduino is 0");
        }

    } catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return ioDeviceList;
}

void IODeviceRepository::setDefaultDatabase(QSqlDatabase db) {
    BsfDbconfig dbConfig = BsfDbconfig();

    if (!QSqlDatabase::contains(dbConfig.defaultConnection)) {
        db = QSqlDatabase::addDatabase(dbConfig.database, dbConfig.defaultConnection);
    } else {
        qDebug("set database name");
        db = QSqlDatabase::database(dbConfig.defaultConnection);
    }
    db.setDatabaseName(dbConfig.databaseName);
}
