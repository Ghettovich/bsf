#ifndef BSF_RELAY_H
#define BSF_RELAY_H

#include <domain/iodevice.h>

class Relay : public IODevice {

public:
    Relay(int id, IO_DEVICE_HIGH_LOW deviceState);
    bool isDeviceStateLOW() const override;
};


#endif //BSF_RELAY_H
