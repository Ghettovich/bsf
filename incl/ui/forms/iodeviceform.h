#ifndef BSF_IODEVICEFORM_H
#define BSF_IODEVICEFORM_H

#include <QtWidgets/QWidget>
#include <QNetworkConfiguration>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork/QNetworkDatagram>
#include <QtNetwork/QUdpSocket>
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
    int selectedIODeviceTypeId = 0;
    int currentState;
    QList<QWidget *> ioDeviceFormList;

    PayloadService * payloadService = nullptr;
    IODeviceRepository *ioDeviceRepository = nullptr;
    StateCodeRepository *stateCodeRepository = nullptr;
    Arduino *arduino = nullptr;
    QWidget *parent = nullptr;
    QGridLayout *grid = nullptr;
    Ui::IODeviceForm *ui;

    bool parseDatagram(QString& digits);
    // NETWORK
    QNetworkReply *reply = nullptr;
    //QHostAddress *qHostAddress = nullptr;
    //QUdpSocket *udpSocket = nullptr;
    //QNetworkAccessManager networkAccessManager;

    void createArduinoDeviceTypeIOComboBox();
    void createWeightSensorWidgets();
    void createDetectionSensorWidgets();
    void createRelayFormWidgets();
    void createIODeviceWidgets(int maxColumnCount, int _ioDeviceType);
    void killChildWidgets();
    void updateButtonStatesInFormList();
    void updateSensorStateInFormList();
    void updateUIWidgetsWithNewState(int stateCode);

private slots:
//    void httpFinished();
//    void httpReadyRead();
//    void httpError();
    void createIODeviceTypeFormList(const QString &deviceType);
//    void onIncomingDatagrams();
    void processNetworkDatagram(const QNetworkDatagram& datagram);
};
#endif //BSF_IODEVICEFORM_H
