#ifndef BSF_DEVICEMANAGER_H
#define BSF_DEVICEMANAGER_H

#include <QtWidgets/QWidget>


class DeviceManager {

public:
    void createDeviceWidgets(QWidget *parent);
    void addNewDeviceWdiget(QWidget *parent);

    QHBoxLayout *deviceHbox;
    QList<ArduinoDevice *> arduinoDevices;
};


#endif //BSF_DEVICEMANAGER_H
