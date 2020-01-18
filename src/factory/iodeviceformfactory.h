#ifndef BSF_IODEVICEFORMFACTORY_H
#define BSF_IODEVICEFORMFACTORY_H

#include <ui/forms/detectionsensorform.h>
#include <ui/forms/weightsensorform.h>
#include <ui/forms/relayform.h>

class IODeviceFormFactory {

public:
    static QWidget* getIODeviceForm(int type, QWidget *parent, IODevice *ioDevice)
    {
        if (type == IODeviceTypeEnum::DETECTIONSENSOR) {
            qDebug("%s", qUtf8Printable("created form from factory"));
            return new DetectionSensorForm(parent, ioDevice);
        }
        if (type == IODeviceTypeEnum::RELAY) {
            return new RelayForm(parent, ioDevice);
        }
        return nullptr;
    }

    static QWidget * weightSensorForm(QWidget *parent, WeightCensor * weightSensor)
    {
        return new WeightSensorForm(parent, weightSensor);
    }
};
#endif //BSF_IODEVICEFORMFACTORY_H
