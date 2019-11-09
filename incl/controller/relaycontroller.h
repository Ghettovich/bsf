#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include "incl/repo/relayrepo.h"
#include "incl/repo/actionarduinorepo.h"

#ifndef BSF_RELAYCONTROLLER_H
#define BSF_RELAYCONTROLLER_H

class RelayController {

public:
    void createTestRelayWidgets();
    QGridLayout *grid{};
private:
    RelayRepository *relayRepository = new RelayRepository;
    ActionArduinoRepository *actionArduinoRepository = new ActionArduinoRepository;
};
#endif //BSF_RELAYCONTROLLER_H
