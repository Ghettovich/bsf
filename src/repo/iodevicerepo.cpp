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

QList<IODevice> IODeviceRepository::getArduinoIODevices(int id) {
    QString queryString = "SELECT * FROM io_device WHERE arduino_id=:id";
    QList<IODevice> ioDeviceList;

    try {
        QSqlQuery query(getQSqlDatabase());
        query.prepare(queryString);
        query.bindValue(":id", id);

        if (query.exec()) {
            while (query.next()) {
                IODevice ioDevice;
                ioDevice.id = query.value("id").toInt();
                ioDevice.arduino_id = query.value("arduino_id").toInt();
                ioDevice.type_id = query.value("type_id").toInt();
                ioDevice.desc = query.value("description").toString();
                ioDeviceList.append(ioDevice);
            }
            getQSqlDatabase().close();
        }
    } catch (std::exception &e) {
        qDebug(e.what());
    }

    return ioDeviceList;
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

QSqlDatabase IODeviceRepository::getQSqlDatabase() {
    return QSqlDatabase::database(bsfDbConfig->getDefaultConnection());
}
