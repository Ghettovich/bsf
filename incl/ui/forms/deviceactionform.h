#ifndef BSF_DEVICEACTIONFORM_H
#define BSF_DEVICEACTIONFORM_H

#include <QtWidgets/QWidget>
#include <QLabel>
#include <QString>
#include <incl/repo/arduinorepo.h>
#include <incl/repo/actionarduinorepo.h>
#include "incl/ui/forms/iodeviceform.h"

namespace Ui {
    class DeviceActionForm;
}

class DeviceActionForm : public QWidget {
Q_OBJECT

public:
    explicit DeviceActionForm(QWidget *_parent = nullptr);
    virtual ~DeviceActionForm();

    QWidget *parent = nullptr;

private:
    QList<Arduino> arduinoList;
    QList<Action> actionList;
    Arduino selectedArduino;
    IODevice selectedIODevice;
    //ArduinoAction *selectedArduinoAction = nullptr;
    ArduinoRepository *arduinoRepository = nullptr;
    ActionArduinoRepository *actionArduinoRepository = nullptr;
    IODeviceForm *ioDeviceForm = nullptr;

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
