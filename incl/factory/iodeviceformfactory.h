#ifndef BSF_IODEVICEFORMFACTORY_H
#define BSF_IODEVICEFORMFACTORY_H

#include <memory>
#include <QtWidgets/QWidget>
#include <incl/domain/iodevicetype.h>
#include <incl/ui/forms/detectionsensorform.h>
#include <incl/ui/forms/weightsensorform.h>
#include <incl/ui/forms/relayform.h>

class IODeviceFormFactory {

public:
    static QWidget* getIODeviceForm(int type, QWidget *parent, IODevice *ioDevice)
    {
        if (type == IODeviceTypeEnum::DETECTIONSENSOR)
            return new DetectionSensorForm(parent, ioDevice);
        if (type == IODeviceTypeEnum::WEIGHTSENSOR)
            return new WeightSensorForm(parent, ioDevice);
        if (type == IODeviceTypeEnum::RELAY)
            return new RelayForm(parent);
        return nullptr;
    }
};
#endif //BSF_IODEVICEFORMFACTORY_H
