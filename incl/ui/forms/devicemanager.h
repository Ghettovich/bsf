#ifndef BSF_DEVICEMANAGER_H
#define BSF_DEVICEMANAGER_H

#include <QtWidgets/QWidget>


class DeviceManager {

public:
    void createDeviceWidgets();
    void updateArduinoDevice(const arduino &arduinoDevice);

    QHBoxLayout *deviceHbox;
    QList<arduino> arduinos;

private:
    DbManager dbManager = DbManager(R"(../test/database/dbTest.db)");
};
#endif //BSF_DEVICEMANAGER_H
