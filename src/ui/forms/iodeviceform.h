#ifndef BSF_IODEVICEFORM_H
#define BSF_IODEVICEFORM_H

#include <domain/arduino.h>
#include <domain/iodevice.h>
#include <domain/iodevicetype.h>
#include <domain/weightcensor.h>
#include <service/payloadservice.h>
#include <QtWidgets/QWidget>
#include <QtCore/QVector>
#include <QtWidgets/QGridLayout>

namespace Ui {
    class IODeviceForm;
}

class IODeviceForm : public QWidget {
Q_OBJECT

public:
    explicit IODeviceForm(QWidget *parent = nullptr);
    virtual ~IODeviceForm();

private:
    Arduino arduino;
    IODeviceType ioDeviceType;
    QVector<IODevice> ioDeviceList;
    QVector<IODeviceType> ioDeviceTypeList;
    QVector<WeightCensor> weightSensorList;
    PayloadService payloadService;

    QGridLayout *grid = nullptr;
    Ui::IODeviceForm *ui;

    void createWeightSensorWidgets();
    void createDetectionSensorWidgets();
    void createRelayFormWidgets();
    void createIODeviceWidgets(int maxColumnCount, int _ioDeviceType);
    void killChildWidgets();

public slots:
    void onCreateIODeviceTypeFormList(int index);
    void onCreateArduinoDeviceTypeIOComboBox(QVector<IODeviceType>);

signals:
    void createIODeviceTypeFormList(int arduinoId);




};
#endif //BSF_IODEVICEFORM_H
