#ifndef BSF_DEVICEACTIONFORM_H
#define BSF_DEVICEACTIONFORM_H

#include "iodeviceform.h"
#include <QString>
#include <QtWidgets/QWidget>
#include <repo/actionarduinorepo.h>
#include <repo/arduinorepo.h>

namespace Ui {
    class DeviceActionForm;
}

class DeviceActionForm : public QWidget {
Q_OBJECT

public:
    explicit DeviceActionForm(QWidget *_parent);
    virtual ~DeviceActionForm();
    IODeviceForm *ioDeviceForm = nullptr;

private:
    QWidget *parent = nullptr;
    QList<Arduino> arduinoList;
    QList<Action> actionList;
    Arduino selectedArduino;
    ArduinoRepository *arduinoRepository = nullptr;
    ActionArduinoRepository *actionArduinoRepository = nullptr;
    Ui::DeviceActionForm *ui = nullptr;

    void createComboBoxItems();
    void updateLabels();
    void createIODeviceForm();
    void updateIODeviceForm();
    void createStateActionItemList();

private slots:
    void updateWidget(const QString &arduino_id);

};
#endif //BSF_DEVICconst EACTION&FORM_H
