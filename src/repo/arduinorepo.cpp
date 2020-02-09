#include "arduinorepo.h"
#include <domain/iodevicetype.h>
#include <domain/detectionsensor.h>
#include <domain/relay.h>
#include <domain/weightcensor.h>
#include <data/bsfdatabaseconfig.h>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>

ArduinoRepository::ArduinoRepository() = default;

QVector<Arduino> ArduinoRepository::getAllActiveArduino() {
    QString queryString = "SELECT id, name, ipaddress, port, description FROM arduino";
    QVector<Arduino> arduinoList;

    try {
        QSqlDatabase db;
        setDefaultDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.exec(queryString);

        while (query.next()) {
            Arduino arduino = Arduino(query.value("id").toInt());
            arduino.setDesc(query.value("description").toString());
            arduino.setIpAddress(query.value("ipaddress").toString());
            arduino.setName(query.value("name").toString());
            arduino.setPort(query.value("port").toInt());
            arduinoList.append(arduino);
        }

        db.close();
    } catch (std::exception &e) {
        printf("%s", e.what());
    }
    return arduinoList;
}

Arduino ArduinoRepository::getArduino(int id) {
    Arduino arduino;
    QString queryString = "SELECT id, name, ipaddress, port, description FROM arduino WHERE id =:id";

    try {
        QSqlDatabase db;
        setDefaultDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":id", id);
        query.exec();

        if (query.first()) {
            arduino = Arduino(query.value("id").toInt());
            arduino.setDesc(query.value("description").toString());
            arduino.setIpAddress(query.value("ipaddress").toString());
            arduino.setName(query.value("name").toString());
            arduino.setPort(query.value("port").toInt());
            return arduino;
        }

        db.close();
    } catch (std::exception &e) {
        printf("%s", e.what());
    }

    return Arduino(0);
}

void ArduinoRepository::updateArduino(const Arduino &arduinoDevice) {
    QString queryString = "UPDATE arduino SET description=:desc, ipaddress=:ipaddress, name=:name, port=:port WHERE id=:id";

    try {
        if (arduinoDevice.getId() > 0) {
            QSqlDatabase db;
            setDefaultDatabase(db);
            QSqlQuery query(db);

            db.open();
            query.prepare(queryString);
            query.bindValue(":desc", arduinoDevice.getDesc());
            query.bindValue(":ipaddress", arduinoDevice.getIpAddress());
            query.bindValue(":name", arduinoDevice.getName());
            query.bindValue(":port", arduinoDevice.getPort());
            query.bindValue(":id", arduinoDevice.getId());

            if (query.exec()) {
                printf("\nExecuted update");
            }
            db.close();
        }

    } catch (std::exception &e) {
        printf("%s", e.what());
    }
}

QVector<Arduino *> ArduinoRepository::getAllActiveArduinoWithIODevices() {
    QVector<Arduino *> arduinoList;
    QString queryString = "SELECT io.arduino_id, ard.description AS ard_desc, ard.ipaddress, ard.name, ard.port, io.id AS io_id, io.type_id, io.action_id, io.description AS io_desc, io_dev_type.type AS io_type, act.code, act.url, act.description AS act_desc "
                          "FROM io_device io "
                          "INNER JOIN io_device_type io_dev_type ON io.type_id = io_dev_type.id "
                          "INNER JOIN arduino ard ON ard.id = io.arduino_id "
                          "INNER JOIN action act ON act.id = io.action_id "
                          "ORDER BY io.arduino_id ";

    try {
        QSqlDatabase db;
        setDefaultDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.exec(queryString);

        //Arduino * arduino = nullptr;
        int currentId = 0, prevId = 0;
        while (query.next()) {
            IODevice *ioDevice = nullptr;

            // IODeviceType properties
            IODeviceType ioDeviceType = IODeviceType(query.value("type_id").toInt());
            ioDeviceType.setType(query.value("io_type").toString());
            IODeviceType::identifyIODeviceTypeEnum(ioDeviceType);

            if(ioDeviceType.getIODeviceType() == IODeviceType::DETECTIONSENSOR) {
                printf("\nADDED DETECTION SENSOR");
                ioDevice = new DetectionSensor(query.value("io_id").toInt(), IODevice::HIGH);
            } else if (ioDeviceType.getIODeviceType() == IODeviceType::RELAY) {
                printf("\nADDED RELAY");
                ioDevice = new Relay(query.value("io_id").toInt(), IODevice::HIGH);
            } else if (ioDeviceType.getIODeviceType() == IODeviceType::WEIGHTSENSOR) {
                printf("\nADDED WEIGHT SENSOR");
                ioDevice = new WeightCensor(query.value("io_id").toInt(), IODevice::HIGH);
            }
            else {
                printf("\nUnkown device");
            }
            // Action properties
            Action action = Action(query.value("action_id").toInt());
            action.setCode(query.value("code").toString());
            action.setUrl(query.value("url").toString());
            action.setDescription(query.value("act_desc").toString());
            // call setters after null pointer check
            if(ioDevice != nullptr) {
                ioDevice->setIoDeviceType(ioDeviceType);
                ioDevice->setAction(action);
            }


            currentId = query.value("arduino_id").toInt();

            if (currentId != prevId) {
                auto arduino = new Arduino(currentId);
                //auto ioDeviceList = new QVector<IODevice *>();
                //arduino->setIoDeviceList(ioDeviceList);
                arduino->setDesc(query.value("ard_desc").toString());
                arduino->setIpAddress(query.value("ipaddress").toString());
                arduino->setName(query.value("name").toString());
                arduino->setPort(query.value("port").toInt());
                arduinoList.append(arduino);
                arduino->addIODevice(ioDevice);
                printf("\nadded arduino with io device");
            }
            else {
                arduinoList.last()->addIODevice(ioDevice);
            }


            // assign current id to prev. to check if query contains new arduino id
            prevId = currentId;
        }

        db.close();
    } catch (std::exception &e) {
        printf("%s", e.what());
    }
    return arduinoList;
}



void ArduinoRepository::setDefaultDatabase(QSqlDatabase &db) {
    BsfDbconfig dbConfig = BsfDbconfig();

    if (!QSqlDatabase::contains(dbConfig.defaultConnection)) {
        db = QSqlDatabase::addDatabase(dbConfig.database, dbConfig.defaultConnection);
    } else {
        db = QSqlDatabase::database(dbConfig.defaultConnection);
    }
    db.setDatabaseName(dbConfig.databaseName);
}
