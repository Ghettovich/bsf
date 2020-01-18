#ifndef BSF_DEVICEACTIONFORM_H
#define BSF_DEVICEACTIONFORM_H

#include <QString>
#include <QtWidgets/QWidget>
#include <domain/arduino.h>
#include <repo/actionarduinorepo.h>

namespace Ui {
    class DeviceActionForm;
}

class DeviceActionForm : public QWidget {

    Q_OBJECT

public:
    explicit DeviceActionForm(QWidget *parent);
    virtual ~DeviceActionForm();
    void createComboBoxItems(QList<Arduino>);
    void createStateActionItemList(Arduino,QList<Action>);
    void createListWidget(QList<Action>);
    void updateWidget(int);
    int selectedArduinoId();

private:
    Ui::DeviceActionForm *ui = nullptr;
    Arduino arduino;
    QList<Action> actionList;
    QList<Arduino> arduinoList;
    ActionArduinoRepository actionArduinoRepository;

    void updateLabels();

signals:
    void arduinoIdChange(int arduinoId);

};
#endif //BSF_DEVICEACTIONFORM_H
