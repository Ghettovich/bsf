#ifndef BSF_IODEVICEREPO_H
#define BSF_IODEVICEREPO_H

#include <incl/data/bsfdatabaseconfig.h>
#include <QtSql/QSqlDatabase>
#include <incl/domain/iodevice.h>
#include <incl/domain/iodevicetype.h>

class IODeviceRepository {

public:
    IODeviceRepository();
    QList<IODeviceType> getArduinoIODeviceTypes(int id);
    QList<IODevice> getArduinoIODeviceList(int arduino_id, int ioDeviceType) ;

private:
    BsfDbconfig *bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
};


#endif //BSF_IODEVICEREPO_H
