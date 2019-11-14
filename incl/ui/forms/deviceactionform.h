#ifndef BSF_DEVICEACTIONFORM_H
#define BSF_DEVICEACTIONFORM_H

#include <QtWidgets/QWidget>
#include <QLabel>
#include <incl/domain/actionarduino.h>
#include <incl/repo/arduinorepo.h>
#include <incl/repo/actionarduinorepo.h>

namespace Ui {
    class DeviceActionForm;
}

class DeviceActionForm : public QWidget {

public:
    explicit DeviceActionForm(QWidget *_parent = nullptr);
    virtual ~DeviceActionForm();

    QWidget *parent = nullptr;

private:
    QLabel *lblIp = nullptr;
    QList<Arduino> arduinoList;
    QList<Action> actionList;
    Arduino selectedArduino;
    //ArduinoAction *selectedArduinoAction = nullptr;
    ArduinoRepository *arduinoRepository = nullptr;
    ActionArduinoRepository *actionArduinoRepository = nullptr;
    Ui::DeviceActionForm *ui = nullptr;

    void createComboBoxItems();
    void createStateActionItemList();
};
#endif //BSF_DEVICEACTIONFORM_H
