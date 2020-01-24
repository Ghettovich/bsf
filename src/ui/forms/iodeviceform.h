#ifndef BSF_IODEVICEFORM_H
#define BSF_IODEVICEFORM_H

#include <domain/arduino.h>
#include <domain/iodevice.h>
#include <domain/iodevicetype.h>
#include <domain/weightcensor.h>
#include <service/payloadservice.h>
#include <service/networkservice.h>
#include <QtWidgets/QWidget>
#include <QtCore/QVector>
#include <QtWidgets/QGridLayout>

namespace Ui {
    class IODeviceForm;
}

class IODeviceForm : public QWidget {
Q_OBJECT

public:
    IODeviceForm(QWidget *parent, const Qt::WindowFlags &f);
    virtual ~IODeviceForm();
    void onCreateArduinoDeviceTypeIOComboBox(Arduino&, QVector<IODeviceType>);

private:
    Arduino arduino;
    IODeviceType selectedIODeviceType;
    QVector<IODevice> ioDeviceList;
    QVector<IODeviceType> ioDeviceTypeList;
    QVector<WeightCensor> weightSensorList;

    PayloadService payloadService;
    NetworkService networkService;
    QVBoxLayout *vbox = nullptr;
    QGridLayout *grid = nullptr;

    Ui::IODeviceForm *ui;
    void createWeightSensorWidgets();
    void createDetectionSensorWidgets();
    void createRelayFormWidgets();
    void createIODeviceWidgets(int maxColumnCount);
    void killChildWidgets();

public slots:
    void onCreateIODeviceTypeFormList(int index);
    void onSendRequest(const QUrl&);
    void onUpdateWithNewStateIODevice(QVector<IODevice>);

signals:
    void createIODeviceTypeFormList(int arduinoId);




};
#endif //BSF_IODEVICEFORM_H
