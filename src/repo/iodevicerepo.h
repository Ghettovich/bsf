#ifndef BSF_IODEVICEREPO_H
#define BSF_IODEVICEREPO_H

#include <domain/iodevice.h>
#include <domain/iodevicetype.h>
#include <QVector>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class IODeviceRepository {

public:
    explicit IODeviceRepository();
    IODeviceType getIODeviceType(int ioDeviceTyperId);
    QVector<IODeviceType> getArduinoIODeviceTypes(int id);
    QVector<IODevice *> getArduinoIODeviceList(int, int, IODeviceType::IO_DEVICE_TYPE);

private:

    void setDefaultDatabase(QSqlDatabase db);
    void createRelayList(QSqlQuery&, QVector<IODevice *>&);
    void createWeightSensorList(QSqlQuery&, QVector<IODevice *>&);
    void createDetectionSensorList(QSqlQuery&, QVector<IODevice *>&);
};


#endif //BSF_IODEVICEREPO_H
