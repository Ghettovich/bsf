#ifndef BSF_IODEVICEREPO_H
#define BSF_IODEVICEREPO_H

#include <bsfdatabaseconfig.h>
#include <iodevice.h>
#include <iodevicetype.h>
#include <QVector>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class IODeviceRepository {

public:
    explicit IODeviceRepository(const QString& connection = "");
    IODeviceType getIODeviceType(int ioDeviceTyperId);
    QVector<IODeviceType> getArduinoIODeviceTypes(int id);
    QVector<IODevice *> getArduinoIODeviceList(int, int, IODeviceType::IO_DEVICE_TYPE);

private:
    BsfDbconfig bsfDbConfig;
    void createRelayList(QSqlQuery&, QVector<IODevice *>&);
    void createWeightSensorList(QSqlQuery&, QVector<IODevice *>&);
    void createDetectionSensorList(QSqlQuery&, QVector<IODevice *>&);
};


#endif //BSF_IODEVICEREPO_H
