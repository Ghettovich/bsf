#ifndef BSF_RELAYCONTROLLER_H
#define BSF_RELAYCONTROLLER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtNetwork/QUdpSocket>
#include <incl/repo/iodevicerepo.h>
#include <incl/ui/forms/relayform.h>
#include <incl/repo/arduinorepo.h>

class RelayController : public QObject {

    Q_OBJECT

public:
    explicit RelayController(QWidget *_parent = nullptr);
    void createTestRelayWidgets();
    void updateWidgetWithRelayStates();

    QWidget *parent = nullptr;
    QGridLayout *grid = nullptr;

private:
    QList<RelayForm *> relayFormList;
    Arduino arduino = Arduino();
    QList<IODevice> ioDeviceList;
    ArduinoRepository *arduinoRepository = nullptr;
    IODeviceRepository *ioDeviceRepository = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QUdpSocket *udpSocketListener = nullptr;
    QHostAddress *bcast = nullptr;
    qint16 port = 0;

private slots:
    void processPendingDatagrams();
    void onListenUDPackets();
};
#endif //BSF_RELAYCONTROLLER_H
