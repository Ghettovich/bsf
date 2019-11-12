#ifndef BSF_RELAYCONTROLLER_H
#define BSF_RELAYCONTROLLER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <incl/domain/actionarduino.h>
#include "incl/repo/relayrepo.h"
#include "incl/repo/actionarduinorepo.h"

class RelayController : public QObject {

public:
    explicit RelayController();
    void createTestRelayWidgets();
    void updateWidgetWithRelayStates();
    QGridLayout *grid{};

private:
    QList<QWidget *> widgetList;
    QList<ArduinoAction> arduinoActionList;
    //RelayRepository *relayRepository = new RelayRepository();
    ActionArduinoRepository *actionArduinoRepository = nullptr;
    QUdpSocket *udpSocket = nullptr;

private slots:
    void processPendingDatagrams();
};
#endif //BSF_RELAYCONTROLLER_H
