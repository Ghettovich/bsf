#include "ui_iodeviceform.h"
#include "incl/ui/forms/iodeviceform.h"
#include <incl/factory/iodeviceformfactory.h>

IODeviceForm::IODeviceForm(QWidget *_parent, Arduino *_arduino) :
        QWidget(_parent), ui(new Ui::IODeviceForm) {
    ui->setupUi(this);
    arduino = _arduino;

    //SERVICE
    payloadService = new PayloadService(this);
    payloadService->requestStatePayload();

    // DATA
    stateCodeRepository = new StateCodeRepository;
    ioDeviceRepository = new IODeviceRepository;
    createArduinoDeviceTypeIOComboBox();

    // LAYOUT
    grid = new QGridLayout(ui->groupBoxConnectedIO);
    grid->setContentsMargins(5, 40, 5, 5);
    // CREATE widgets with first item in Combo Box
    createIODeviceTypeFormList(ui->comboBoxIODevices->itemText(0));

    // SIGNALS & SLOTS
    // COMBO BOX
    connect(ui->comboBoxIODevices, SIGNAL(currentIndexChanged(
                                                  const QString&)), this, SLOT(createIODeviceTypeFormList(
                                                                                       const QString&)));
}

IODeviceForm::~IODeviceForm() {
    delete ui;
}

void IODeviceForm::createArduinoDeviceTypeIOComboBox() {
    ioDeviceTypeList = ioDeviceRepository->getArduinoIODeviceTypes(arduino->id);

    if(!ioDeviceTypeList.empty()) {
        ui->comboBoxIODevices->setEnabled(true);
        qDebug("got id: %s", qUtf8Printable(QString::number(arduino->id)));
        for (auto &_ioDeviceType: ioDeviceTypeList) {
            ui->comboBoxIODevices->addItem(_ioDeviceType.type, _ioDeviceType.id);
        }
    } else {
        qDebug("%s", qUtf8Printable("no io device types"));
        ui->comboBoxIODevices->setEnabled(false);
    }

}

void IODeviceForm::updateArduinoDeviceTypeIOComboBox(Arduino &_arduino) {
    ui->comboBoxIODevices->clear();
    ioDeviceTypeList.clear();
    arduino = &_arduino;
    createArduinoDeviceTypeIOComboBox();
}

void IODeviceForm::updateButtonStatesInFormList() {
//    QNetworkRequest request;
//    request.setUrl(QUrl("http://[fd54:d174:8676:0001:7269:74ff:fe2d:3031]/relay-state"));
//    reply = networkAccessManager.get(request);
}

void IODeviceForm::updateSensorStateInFormList() {
//    QNetworkRequest request;
//    request.setUrl(QUrl("http://[fd54:d174:8676:0001:7269:74ff:fe2d:3031]/sensor-state"));
//    reply = networkAccessManager.get(request);

//    qInfo() << "writing datagram...\nGot port =" << QString::number(arduino->port) << "\nWith IP ="
//            << arduino->ipAddress;
}

void IODeviceForm::createWeightSensorWidgets() {
    qDebug("%s", qUtf8Printable("creating weight sensor widget..."));
    int maxColumnCount = 2;
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::WEIGHTSENSOR);
}

void IODeviceForm::createDetectionSensorWidgets() {
    qDebug("%s", qUtf8Printable("creating detection sensor widgets..."));
    int maxColumnCount = 2;
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::DETECTIONSENSOR);
    updateSensorStateInFormList();
}

void IODeviceForm::createRelayFormWidgets() {
    qDebug("%s", qUtf8Printable("creating relay widgets..."));
    int maxColumnCount = 2;
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::RELAY);
    // call service here

    updateButtonStatesInFormList();
}

void IODeviceForm::createIODeviceWidgets(int maxColumnCount, int _ioDeviceType) {
    int column = 0, row = 0;
    ioDeviceType = ioDeviceRepository->getIODeviceType(_ioDeviceType);

    for (auto ioDevice: ioDeviceList) {
        if (column == maxColumnCount) {
            column = 0;
            row++;
        }
        ioDevice->setIoDeviceType(*ioDeviceType);
        auto *ioDeviceForm = IODeviceFormFactory::getIODeviceForm(_ioDeviceType, this, ioDevice);
        ioDeviceFormList.append(ioDeviceForm);
        grid->addWidget(ioDeviceForm, row, column, Qt::AlignLeft);
        column++;
    }
    ui->groupBoxConnectedIO->setLayout(grid);
    ui->groupBoxConnectedIO->layout()->setSizeConstraint(QLayout::SetMinimumSize);
}

void IODeviceForm::killChildWidgets() {
    for (auto *form: ioDeviceFormList) {
        form->deleteLater();
        qDebug("%s", qUtf8Printable("child deleted"));
    }
}

/* PRIVATE SLOTS */
void IODeviceForm::createIODeviceTypeFormList(const QString &deviceType) {
    killChildWidgets();
    ioDeviceList.clear();
    ioDeviceFormList.clear();

    qDebug("%s", qUtf8Printable(deviceType));

    if (QString::compare(deviceType, "weightsensor") == 0) {
        selectedIODeviceTypeId = IODeviceTypeEnum::WEIGHTSENSOR;
        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::WEIGHTSENSOR);
        createWeightSensorWidgets();
    } else if (QString::compare(deviceType, "detectionsensor") == 0) {
        selectedIODeviceTypeId = IODeviceTypeEnum::DETECTIONSENSOR;
        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::DETECTIONSENSOR);
        createDetectionSensorWidgets();
    } else if (QString::compare(deviceType, "relay") == 0) {
        selectedIODeviceTypeId = IODeviceTypeEnum::RELAY;
        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::RELAY);
        createRelayFormWidgets();
    } else {
        qDebug("%s", qUtf8Printable("Could not find matching device type"));
    }
}

//void IODeviceForm::httpReadyRead() {
//    qInfo() << "got reply: " << reply->readAll().constData();
//    //QString stateMessage = "";
//    QString digits = "";
//
//
//    if (parseDatagram(digits)) {
//        int stateCode = digits.toInt();
//        qInfo() << "state code =" << QString::number(stateCode);
//        qInfo() << "digits" << digits;
//        updateUIWidgetsWithNewState(stateCode);
//    } else {
//        qInfo() << "failed to parse datagram";
//    }
//}
//
//void IODeviceForm::httpFinished() {
//    qInfo() << "finished called" << "\nReply = " << reply->readAll().constData();
//}
//
//void IODeviceForm::httpError() {
//    qInfo() << "got http error" << reply->error();
//}
//
//void IODeviceForm::onIncomingDatagrams() {
//    QByteArray datagram;
//    qInfo() << "got incoming udp packets...";
//
//    while (udpSocket->hasPendingDatagrams()) {
//        datagram.resize(int(udpSocket->pendingDatagramSize()));
//        QNetworkDatagram data = udpSocket->receiveDatagram();
//        processNetworkDatagram(data);
//    }
//}

void IODeviceForm::processNetworkDatagram(const QNetworkDatagram &datagram) {
    qInfo() << "raw data: " << datagram.data();
    QString stateMessage = "";
    //QByteArray data = datagram.data();
    QString digits = "";


    if (parseDatagram(digits)) {
        int stateCode = digits.toInt();
        qInfo() << "state code =" << QString::number(stateCode);
        qInfo() << "digits" << digits;
        updateUIWidgetsWithNewState(stateCode);
    } else {
        qInfo() << "failed to parse datagram";
    }
}

// allows only a single CSV value in reply
bool IODeviceForm::parseDatagram(QString& digits) {
    bool isParsed = false;
    QByteArray data(reply->readAll());

    for (QChar c : data) {

        if (c.isDigit()) {
            digits.append(c);
        } else {
            break;
        }
    }
    digits.toInt(&isParsed);
    return isParsed;
}

void IODeviceForm::updateUIWidgetsWithNewState(int stateCode) {
    QString stateMessage = "";
    QByteArray data = reply->readAll();

    qInfo() << "got state code = " << QString::number(stateCode);

    switch (stateCode) {
        case StateCodeEnum::READY :
            currentState = StateCodeEnum::READY;
            setStatusTip("MACHINE READY FOR ACTION!");
            break;
        case IODeviceTypeEnum::WEIGHTSENSOR :
            qInfo() << "got update for weight";
            break;
        case IODeviceTypeEnum::RELAY :
            stateMessage = data.right(8).trimmed();
            qInfo() << "got new states for RELAY";
            break;
        case IODeviceTypeEnum::DETECTIONSENSOR :
            stateMessage = data.right(2).trimmed();
            qInfo() << "got new states for DETECTIONSENSOR";
            break;
        case StateCodeEnum::LIFT_STUCK :
            currentState = StateCodeEnum::LIFT_STUCK;
            setStatusTip("LIFT STUCK, MANUAL OPERATION REQUIRED");
            break;
        default:
            break;
    }

    qInfo() << "msg after trim: " << stateMessage;

    if (selectedIODeviceTypeId == stateCode) {
        // setting the correct state for each widget is depended on how relayFormList is sorted
        // in the used sql statements its ordered on id, edit carefully
        for (int i = 0; i < stateMessage.length(); ++i) {
            qInfo() << "state (1 or 0) is = " << stateMessage.at(i);
            if (stateCode == IODeviceTypeEnum::WEIGHTSENSOR) {

            } else if (stateCode == IODeviceTypeEnum::DETECTIONSENSOR) {
                auto f = dynamic_cast<DetectionSensorForm *>(ioDeviceFormList[i]);
                qInfo() << "Object name =" << f->objectName();
                //emit f->onSensorChange(stateMessage.at(i));
            } else if (stateCode == IODeviceTypeEnum::RELAY) {
                auto f = dynamic_cast<RelayForm *>(ioDeviceFormList[i]);
                qInfo() << "Object name =" << f->objectName();
                //emit f->setRelayButtonState(stateMessage.at(i));
            }
        }
    }
}


