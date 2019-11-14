#ifndef BSF_DEVICEACTIONFORM_H
#define BSF_DEVICEACTIONFORM_H

#include <QtWidgets/QWidget>
#include <QLabel>
#include <incl/domain/actionarduino.h>
#include <incl/repo/arduinorepo.h>
#include <incl/repo/actionarduinorepo.h>
#include "incl/ui/forms/iodeviceform.h"

namespace Ui {
    class DeviceActionForm;
}

class DeviceActionForm : public QWidget {

public:
    explicit DeviceActionForm(QWidget *_parent = nullptr);
    virtual ~DeviceActionForm();

    QWidget *parent = nullptr;

private:
    QList<Arduino> arduinoList;
    QList<Action> actionList;
    Arduino selectedArduino;
    ArduinoAction *selectedArduinoAction = nullptr;
    ArduinoRepository *arduinoRepository = nullptr;
    ActionArduinoRepository *actionArduinoRepository = nullptr;
    IODeviceForm *ioDeviceForm = nullptr;

    Ui::DeviceActionForm *ui = nullptr;

    void createComboBoxItems();
    void createIODeviceForm();
    void createStateActionItemList();
};
#endif //BSF_DEVICEACTIONFORM_H
