#include <QObject>
#include "incl/ui/forms/relayform.h"
#include "incl/controller/relaycontroller.h"

RelayController::RelayController() {
    actionArduinoRepository = new ActionArduinoRepository;
}

void RelayController::createTestRelayWidgets() {
    grid = new QGridLayout;
    arduinoActionList = actionArduinoRepository->getAllArduinoAction();

    for (int i = 0; i < arduinoActionList.length(); ++i) {
        auto *relayForm = new RelayForm;
        relayForm->initWidget(arduinoActionList[i]);

        widgetList.append(relayForm);



        if(i == 0) {
            qDebug("got widgets...");
            grid->addWidget(relayForm, 0, 0, Qt::AlignLeft);
        }
        if(i == 1) {
            grid->addWidget(relayForm, 0, 1, Qt::AlignLeft);
        }
        if(i == 2) {
            grid->addWidget(relayForm, 0, 2, Qt::AlignLeft);
        }
        if(i == 3) {
            grid->addWidget(relayForm, 1, 0, Qt::AlignLeft);
        }
        if(i == 4) {
            grid->addWidget(relayForm, 1, 1, Qt::AlignLeft);
        }
        if(i == 5) {
            grid->addWidget(relayForm, 1, 2, Qt::AlignLeft);
            // TODO: remove break and create function to properly build rows and columns
            break;
        }
    }
}

void RelayController::updateWidgetWithRelayStates() {

//    udpSocket = new QUdpSocket(this);
//    udpSocket->bind(QHostAddress(arduinoActionList.first().arduinoDev.ipAddress),
//            arduinoActionList.first().arduinoDev.port);
//
//    connect(udpSocket, &QUdpSocket::readyRead, this, &RelayController::processPendingDatagrams);
    //QByteArray ba = arduinoAction.action.code.toLocal8Bit();
    //udpSocket->writeDatagram(ba, QHostAddress(arduinoAction.arduinoDev.ipAddress), arduinoAction.arduinoDev.port);

//    for(auto aa: arduinoActionList) {
//
//    }

    for(auto w: widgetList) {

        qInfo() << "Object name = " << w->objectName();
    }
    qInfo() << "update relay states exited";
}

void RelayController::processPendingDatagrams() {

}

