#ifndef BSF_IODEVICEFORM_H
#define BSF_IODEVICEFORM_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <domain/arduino.h>
#include <repo/iodevicerepo.h>
#include <service/payloadservice.h>

namespace Ui {
    class IODeviceForm;
}

class IODeviceForm : public QWidget {
Q_OBJECT

public:
    explicit IODeviceForm(QWidget *_parent = nullptr);
    virtual ~IODeviceForm();

private:
    QList<IODeviceType> ioDeviceTypeList;
    IODeviceType *ioDeviceType = nullptr;
    QList<IODevice *> ioDeviceList;

    QList<QWidget *> ioDeviceFormList;
    PayloadService payloadService;
    //IODeviceRepository ioDeviceRepository;
    Arduino *arduino = nullptr;
    QWidget *parent = nullptr;
    QGridLayout *grid = nullptr;

    Ui::IODeviceForm *ui;
    void createWeightSensorWidgets();
    void createDetectionSensorWidgets();
    void createRelayFormWidgets();
    void createIODeviceWidgets(int maxColumnCount, int _ioDeviceType);
    void killChildWidgets();

public slots:
    void onCreateIODeviceTypeFormList(int ioDeviceTypeId);
    void onCreateArduinoDeviceTypeIOComboBox(int arduinoId);

signals:
    void createIODeviceTypeFormList(int arduinoId);




};
#endif //BSF_IODEVICEFORM_H
