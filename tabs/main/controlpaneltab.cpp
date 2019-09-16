#include <QTabWidget>

#include <headers/tabs/main/controlpaneltab.h>

ControlPanelTab::ControlPanelTab(QTabWidget *parent)
    : QTabWidget(parent)
{
    udpServer = new Server;
    setStatusTip("Operator tab actief");
    createLabels();
    createButtons();
    createPlainTextFields();
}

void ControlPanelTab::createLabels()
{
    lblSensorBottomLeft = new QLabel("Sensor beneden links=LOW", this);
    lblSensorBottomLeft->move(400, 60);
    lblSensorBottomLeft->setMinimumSize(150, 30);

    lblSensorBottomRight = new QLabel("Sensor beneden rechts=LOW", this);
    lblSensorBottomRight->move(610, 60);
    lblSensorBottomRight->setMinimumSize(150, 30);

    lblSensorTopLeft = new QLabel("Sensor boven links=LOW", this);
    lblSensorTopLeft->move(400, 100);
    lblSensorTopLeft->setMinimumSize(150, 30);

    lblSensorTopLeft = new QLabel("Sensor boven rechts=LOW", this);
    lblSensorTopLeft->move(610, 100);
    lblSensorTopLeft->setMinimumSize(150, 30);
}

void ControlPanelTab::createButtons()
{
    btnReset = new QPushButton("Alle relays uit", this);
    btnReset->move(30, 20);
    btnReset->setMinimumWidth(150);
    connect(btnReset, &QPushButton::clicked, this, &ControlPanelTab::onClickReset);

    btnLiftUp = new QPushButton("Lift omhoog", this);
    btnLiftUp->move(30, 60);
    btnLiftUp->setMinimumWidth(150);
    connect(btnLiftUp, &QPushButton::clicked, this, &ControlPanelTab::onClickLiftUp);

    btnLiftDown = new QPushButton("Lift omlaag", this);
    btnLiftDown->move(190, 60);
    btnLiftDown->setMinimumWidth(150);
    connect(btnLiftDown, &QPushButton::clicked, this, &ControlPanelTab::onClickLiftDown);

    btnBinLoad = new QPushButton("Laad bak", this);
    btnBinLoad->move(30, 100);
    btnBinLoad->setMinimumWidth(150);
    connect(btnBinLoad, &QPushButton::clicked, this, &ControlPanelTab::onClickBinLoad);

    btnBinDump = new QPushButton("Dump bak", this);
    btnBinDump->move(190, 100);
    btnBinDump->setMinimumWidth(150);
    connect(btnBinDump, &QPushButton::clicked, this, &ControlPanelTab::onClickBinDump);
}

void ControlPanelTab::createPlainTextFields()
{
    textBroadcastMsg = new QPlainTextEdit(this);
    textBroadcastMsg->setPlaceholderText("Verstuurd bericht...");
    textBroadcastMsg->setDisabled(true);
    textBroadcastMsg->move(830, 20);
    textBroadcastMsg->setMaximumSize(100, 100);

    textRespondMsg = new QPlainTextEdit(this);
    textRespondMsg->setPlaceholderText("Antwoord...");
    textRespondMsg->setDisabled(true);
    textRespondMsg->move(950, 20);
    textRespondMsg->setMaximumSize(100, 100);
}

void ControlPanelTab::onClickReset()
{
    quint16 clientPort = 12309;
    udpServer->broadcastDatagram(clientPort, "INIT");
    textBroadcastMsg->setPlainText("INIT");
    textRespondMsg->setPlainText(udpServer->getResponseMsg());
}

void ControlPanelTab::onClickLiftUp()
{
    quint16 clientPort = 12310;

    if(isLiftUpRelayHigh) {
        udpServer->broadcastDatagram(clientPort, "LIFT_UP_STOP");
        textBroadcastMsg->setPlainText("LIFT_UP_STOP");
        btnLiftUp->setText("Lift omhoog");
    }
    else {
        udpServer->broadcastDatagram(clientPort, "LIFT_UP");
        textBroadcastMsg->setPlainText("LIFT_UP");
        btnLiftUp->setText("Stop lift");
    }

    isLiftUpRelayHigh = !isLiftUpRelayHigh;
    textRespondMsg->setPlainText(udpServer->getResponseMsg());
}

void ControlPanelTab::onClickLiftDown()
{
    quint16 clientPort = 12310;

    if(isLiftDownRelayHigh) {
        udpServer->broadcastDatagram(clientPort, "LIFT_DOWN_STOP");
        textBroadcastMsg->setPlainText("LIFT_DOWN_STOP");
        btnLiftDown->setText("Lift omlaag");
    }
    else {
        udpServer->broadcastDatagram(clientPort, "LIFT_DOWN");
        textBroadcastMsg->setPlainText("LIFT_DOWN");
        btnLiftDown->setText("Stop lift");
    }
    isLiftDownRelayHigh = !isLiftDownRelayHigh;
    qInfo() << "Message: " << QString(udpServer->getResponseMsg());
}

void ControlPanelTab::onClickBinLoad()
{

}

void ControlPanelTab::onClickBinDump()
{

}

void ControlPanelTab::onClickMixer()
{

}

void ControlPanelTab::onClickSlider()
{

}

void ControlPanelTab::onClickBelt()
{

}

void ControlPanelTab::onClickHydro()
{

}
