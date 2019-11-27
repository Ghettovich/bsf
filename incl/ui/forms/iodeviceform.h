#ifndef BSF_IODEVICEFORM_H
#define BSF_IODEVICEFORM_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <incl/domain/iodevicetype.h>
#include <incl/domain/arduino.h>
#include <incl/domain/iodevice.h>
#include <incl/repo/iodevicerepo.h>
#include <incl/ui/forms/relayform.h>

namespace Ui {
    class IODeviceForm;
}

class IODeviceForm : public QWidget {
Q_OBJECT

public:
    explicit IODeviceForm(QWidget *_parent = nullptr, Arduino *_arduino = nullptr);
    virtual ~IODeviceForm();
    void updateArduinoDeviceTypeIOComboBox(Arduino &_arduino);

private:
    QList<IODeviceType> ioDeviceTypeList;
    QList<IODevice> ioDeviceList;
    QList<QWidget *> ioDeviceFormList;

    IODeviceRepository *ioDeviceRepository = nullptr;
    Arduino *arduino = nullptr;
    QWidget *parent = nullptr;
    QGridLayout *grid = nullptr;
    Ui::IODeviceForm *ui;

    void createArduinoDeviceTypeIOComboBox();
    void createWeightSensorWidgets();
    void createDetectionSensorWidgets();
    void createRelayFormWidgets();
    void createIODeviceWidgets(int maxColumnCount, int ioDeviceType);
    void killChildWidgets();


private slots:
    void createIODeviceTypeFormList(const QString &deviceType);
};
#endif //BSF_IODEVICEFORM_H
