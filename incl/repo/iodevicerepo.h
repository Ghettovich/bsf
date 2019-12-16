#ifndef BSF_IODEVICEREPO_H
#define BSF_IODEVICEREPO_H

#include <QtSql/QSqlDatabase>
#include <incl/data/bsfdatabaseconfig.h>
#include <incl/domain/iodevice.h>
#include <incl/domain/iodevicetype.h>
#include <incl/dto/iodevicedto.h>

class IODeviceRepository {

public:
    IODeviceRepository();
    QList<IODeviceType> getArduinoIODeviceTypes(int id);
    IODeviceType *getIODeviceType(int ioDeviceTyperId);
    QList<IODevice *> getArduinoIODeviceList(int arduinoId, int ioDeviceType);
    QList<IODevice *> getArduinoIODeviceList(int arduinoId);


private:
    BsfDbconfig *bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
};


#endif //BSF_IODEVICEREPO_H
