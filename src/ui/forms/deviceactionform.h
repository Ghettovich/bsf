#ifndef BSF_DEVICEACTIONFORM_H
#define BSF_DEVICEACTIONFORM_H

#include <QString>
#include <QtWidgets/QWidget>
#include <arduino.h>
#include <forms/iodeviceform.h>
#include <actionarduinorepo.h>

namespace Ui {
    class DeviceActionForm;
}

class DeviceActionForm : public QWidget {

    Q_OBJECT

public:
    DeviceActionForm(QWidget *parent, const Qt::WindowFlags &f);
    virtual ~DeviceActionForm();
    void createComboBoxItems(QVector<Arduino>);
    void createStateActionItemList(QVector<Action>);
    void createListWidget();
    Arduino& selectedArduino();

public slots:
    void updateWidget(int);

signals:
    void onSelectedArduinoChange(int);

private:
    Ui::DeviceActionForm *ui = nullptr;
    Arduino arduino;
    QVector<Action> actionList;
    QVector<Arduino> arduinoList;
    ActionArduinoRepository actionArduinoRepository;

    void updateLabels();

//signals:
//    void arduinoIdChange(int arduinoId);

};
#endif //BSF_DEVICEACTIONFORM_H
