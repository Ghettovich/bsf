#ifndef BSF_IODEVICEREPO_H
#define BSF_IODEVICEREPO_H

#include <incl/data/bsfdatabaseconfig.h>
#include <QtSql/QSqlDatabase>
#include <incl/domain/iodevice.h>
#include <incl/domain/iodevicetype.h>

class IODeviceRepository {

public:
    IODeviceRepository();
    QList<IODevice> getArduinoIODevices(int id);
    QList<IODeviceType> getArduinoIODeviceTypes(int id);

private:
    BsfDbconfig *bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
};


#endif //BSF_IODEVICEREPO_H
