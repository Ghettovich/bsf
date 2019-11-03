#ifndef BSF_DEVICEMANAGER_H
#define BSF_DEVICEMANAGER_H

#include <QtWidgets/QWidget>


class DeviceManager {

public:
    void createDeviceWidgets();

    QHBoxLayout *deviceHbox;
    QList<arduino> arduinos;
};
#endif //BSF_DEVICEMANAGER_H
