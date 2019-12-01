#ifndef BSF_IODEVICEFORM_H
#define BSF_IODEVICEFORM_H

#include <QtWidgets/QWidget>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>
#include <QtWidgets/QGridLayout>
#include <incl/domain/arduino.h>
#include <incl/repo/iodevicerepo.h>

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
    int selectedIODeviceTypeId = 0;
    QList<QWidget *> ioDeviceFormList;

    IODeviceRepository *ioDeviceRepository = nullptr;
    Arduino *arduino = nullptr;
    QWidget *parent = nullptr;
    QGridLayout *grid = nullptr;

    QUdpSocket *udpSocket = nullptr;
    QUdpSocket *udpSocketListener = nullptr;
    QHostAddress *qHostAddress = nullptr;
    Ui::IODeviceForm *ui;

    void createArduinoDeviceTypeIOComboBox();
    void createWeightSensorWidgets();
    void createDetectionSensorWidgets();
    void createRelayFormWidgets();
    void createIODeviceWidgets(int maxColumnCount, int _ioDeviceType);
    void killChildWidgets();
    void updateButtonStatesInFormList();
    void updateSensorStateInFormList();

private slots:
    void createIODeviceTypeFormList(const QString &deviceType);
    void onProcesPendingDatagrams();
    void onIncomingDatagrams();
    void processNetworkDatagram(const QNetworkDatagram& datagram);
};
#endif //BSF_IODEVICEFORM_H
