#ifndef BSF_IODEVICEFORMFACTORY_H
#define BSF_IODEVICEFORMFACTORY_H

#include <domain/iodevice.h>
#include <domain/weightcensor.h>
#include <domain/iodevicetype.h>
#include <QtWidgets/QWidget>
#include <ui/forms/weightsensorform.h>
#include <ui/forms/relayform.h>
#include <ui/forms/detectionsensorform.h>
#include <ui/forms/deviceactionform.h>
#include <ui/forms/iodeviceform.h>

class IODeviceFormFactory {

public:
    static DetectionSensorForm * createDetectionSensorForm(QWidget *, IODevice&);
    static RelayForm * createRelayForm(QWidget *, IODevice&);
    static WeightSensorForm * createWeightSensorForm(QWidget *, WeightCensor&);
    static DeviceActionForm * createDeviceActiomForm(QWidget*);
    static IODeviceForm * createIODeviceForm(QWidget*);
};
#endif //BSF_IODEVICEFORMFACTORY_H
