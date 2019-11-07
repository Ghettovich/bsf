#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <incl/repo/relayrepo.h>

#ifndef BSF_RELAYCONTROLLER_H
#define BSF_RELAYCONTROLLER_H

class RelayController {

public:
    void createTestRelayWidgets();
    QGridLayout *grid{};
private:
    RelayRepository *relayRepository = new RelayRepository;
};
#endif //BSF_RELAYCONTROLLER_H
