#ifndef BSF_DEVICECONTROLLER_H
#define BSF_DEVICECONTROLLER_H

#include <QHBoxLayout>
#include <QGridLayout>
#include <incl/repo/arduinorepo.h>
#include <incl/domain/log.h>

class DeviceController : public QObject {

public:
    explicit DeviceController(QWidget *parent);
    void createDeviceWidgets();
    void createDeviceActionForm();
    void updateArduinoDevice(const Arduino& arduino);
    void updateArduinoDevice(const Arduino& arduino, const BsfLog& log);

    QWidget *parentWidget = nullptr;
    QHBoxLayout *deviceHbox = nullptr;
    QGridLayout *gridLayout = nullptr;
    QList<Arduino> arduinos;

private:
    ArduinoRepository *arduinoRepository = nullptr;

};
#endif //BSF_DEVICECONTROLLER_H
