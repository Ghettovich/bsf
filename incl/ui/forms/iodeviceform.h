#ifndef BSF_IODEVICEFORM_H
#define BSF_IODEVICEFORM_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <incl/domain/arduino.h>
#include <incl/repo/iodevicerepo.h>
#include <incl/repo/statecoderepo.h>
#include <incl/service/payloadservice.h>

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
    IODeviceType *ioDeviceType = nullptr;
    QList<IODevice *> ioDeviceList;
    QList<QWidget *> ioDeviceFormList;

    PayloadService payloadService;
    IODeviceRepository *ioDeviceRepository = nullptr;
    StateCodeRepository *stateCodeRepository = nullptr;
    Arduino *arduino = nullptr;
    QWidget *parent = nullptr;
    QGridLayout *grid = nullptr;
    Ui::IODeviceForm *ui;

    void createArduinoDeviceTypeIOComboBox();
    void createWeightSensorWidgets();
    void createDetectionSensorWidgets();
    void createRelayFormWidgets();
    void createIODeviceWidgets(int maxColumnCount, int _ioDeviceType);
    void killChildWidgets();

public slots:
    void onUpdateIODeviceState(const QList<IODeviceDTO *>& dtoList);
    void createIODeviceTypeFormList(const QString &deviceType);
};
#endif //BSF_IODEVICEFORM_H
