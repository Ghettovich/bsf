#ifndef BSF_IODEVICEFORM_H
#define BSF_IODEVICEFORM_H

#include <QtWidgets/QWidget>
#include <QNetworkConfiguration>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork/QNetworkDatagram>
#include <QtNetwork/QTcpSocket>
#include <QtWidgets/QGridLayout>
#include <incl/domain/arduino.h>
#include <incl/repo/iodevicerepo.h>
#include <incl/repo/errorcoderepo.h>

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
    ErrorCodeRepository *errorCodeRepository = nullptr;
    Arduino *arduino = nullptr;
    QWidget *parent = nullptr;
    QGridLayout *grid = nullptr;
    Ui::IODeviceForm *ui;

    // NETWORK
    QNetworkReply *reply = nullptr;
    QHostAddress hostAddress;
    QUdpSocket *socket = nullptr;
    QNetworkAccessManager networkAccessManager;

    void createArduinoDeviceTypeIOComboBox();
    void createWeightSensorWidgets();
    void createDetectionSensorWidgets();
    void createRelayFormWidgets();
    void createIODeviceWidgets(int maxColumnCount, int _ioDeviceType);
    void killChildWidgets();
    void updateButtonStatesInFormList();
    void updateSensorStateInFormList();

private slots:
    void httpFinished();
    void httpReadyRead();
    void httpError();
    void createIODeviceTypeFormList(const QString &deviceType);
    void processNetworkDatagram(const QNetworkDatagram& datagram);
};
#endif //BSF_IODEVICEFORM_H
