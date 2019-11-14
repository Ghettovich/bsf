#ifndef BSF_RELAYCONTROLLER_H
#define BSF_RELAYCONTROLLER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <incl/domain/actionarduino.h>
#include "incl/repo/relayrepo.h"
#include "incl/repo/actionarduinorepo.h"
#include "incl/ui/forms/relayform.h"

class RelayController : public QObject {

public:
    explicit RelayController(QWidget *_parent = nullptr);
    void createTestRelayWidgets();
    void updateWidgetWithRelayStates();
    QWidget *parent = nullptr;
    QGridLayout *grid = nullptr;

private:
    QList<RelayForm *> relayFormList;
    QList<ArduinoAction> arduinoActionList;
    ActionArduinoRepository *actionArduinoRepository = nullptr;
    QUdpSocket *udpSocket = nullptr;

private slots:
    void processPendingDatagrams();
};
#endif //BSF_RELAYCONTROLLER_H
