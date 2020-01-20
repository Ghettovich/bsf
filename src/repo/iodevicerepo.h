#ifndef BSF_IODEVICEREPO_H
#define BSF_IODEVICEREPO_H

#include <QtSql/QSqlDatabase>
#include <domain/iodevicetype.h>
#include <domain/iodevice.h>
#include <domain/weightcensor.h>
#include <data/bsfdatabaseconfig.h>

class IODeviceRepository {

public:
    IODeviceRepository();
    QList<IODeviceType> getArduinoIODeviceTypes(int id);
    IODeviceType getIODeviceType(int ioDeviceTyperId);
    QList<IODevice> getArduinoIODeviceList(int arduinoId, int ioDeviceType);
    QList<WeightCensor> getArduinoWeightSensorList(int arduinoId);
    QList<IODevice> getArduinoIODeviceList(int arduinoId);


private:
    BsfDbconfig bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
};


#endif //BSF_IODEVICEREPO_H
