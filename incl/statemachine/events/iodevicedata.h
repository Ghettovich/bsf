#ifndef BSF_IODEVICEDATA_H
#define BSF_IODEVICEDATA_H

#include <incl/statemachine/statemachine.h>
#include <QtCore/QList>
#include <incl/domain/iodevice.h>

struct IODeviceData : public EventData {
public:
    QList<IODevice *> ioDeviceList;
};
#endif //BSF_IODEVICEDATA_H
