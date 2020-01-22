#ifndef BSF_IODEVICEREPO_H
#define BSF_IODEVICEREPO_H


#include <domain/iodevicetype.h>
#include <domain/iodevice.h>
#include <domain/weightcensor.h>
#include <QtSql/QSqlDatabase>

class IODeviceRepository {

public:
    IODeviceRepository();
    IODeviceType getIODeviceType(int ioDeviceTyperId);
    QVector<IODeviceType> getArduinoIODeviceTypes(int id);
    QVector<IODevice> getArduinoIODeviceList(int arduinoId, int ioDeviceType);
    QVector<WeightCensor> getArduinoWeightSensorList(int arduinoId);
    QVector<IODevice> getArduinoIODeviceList(int arduinoId);

private:
    const int weightSensorTypeId = 1, detectionSensorTypeId = 2, relayTypeId = 3;
    void setDefaultDatabase(QSqlDatabase db);
};


#endif //BSF_IODEVICEREPO_H
