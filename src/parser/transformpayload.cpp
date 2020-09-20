#include "transformpayload.h"

void TransformPayload::updateArduinoWithPayload(int &_arduinoId, Arduino::ARDUINO_STATE &newState, QVector<IODevice *>& ioDeviceList, const QByteArray &payload) {
    auto parseError = new QJsonParseError;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));
    QJsonValue arduinoId (jsonDocument["arduinoId"].toInt());
    QJsonObject jsonObject(jsonDocument["iodevices"].toObject());
    QJsonArray items = jsonObject["items"].toArray();

    if (jsonDocument.isNull()) {
        printf("%s", "Failed to create JSON doc.\n");
        printf("error string %s", (char *)parseError->errorString().data());
    }
    if (!jsonDocument.isObject()) {
        printf("%s", "JSON is not an object.\n");
        printf("error string %s", (char *)parseError->errorString().data());
    }
    else {
        _arduinoId = arduinoId.toInt();
        QJsonValue state (jsonDocument["state"]);
        identifyArduinoState(state.toInt(), newState);
        parseIODeviceItemsInPayload(items, ioDeviceList);
    }
}

void TransformPayload::parseIODeviceItemsInPayload(QJsonArray &items, QVector<IODevice *> &ioDeviceList) {

    for (int i = 0; i < items.size(); i++) {
        QJsonObject ioDeviceObject = items[i].toObject();
        if (ioDeviceObject.contains("id")) {

            if(ioDeviceObject["typeId"].toInt() == 1) {
                auto weightSensor = new WeightCensor(ioDeviceObject["id"].toInt()
                        ,ioDeviceObject["low"].toInt() == 0 ? IODevice::HIGH : IODevice::LOW);
                ioDeviceList.append(weightSensor);
            }
            else if(ioDeviceObject["typeId"].toInt() == 2) {
                auto detectSensor = new DetectionSensor(ioDeviceObject["id"].toInt(),
                                                        ioDeviceObject["low"].toInt() == 0 ? IODevice::HIGH : IODevice::LOW);
                ioDeviceList.append(detectSensor);
            }
            else if(ioDeviceObject["typeId"].toInt() == 3) {
                auto relay = new Relay(ioDeviceObject["id"].toInt(),
                                             ioDeviceObject["low"].toInt() == 0 ? IODevice::HIGH : IODevice::LOW);
                ioDeviceList.append(relay);
            }
        }
    }
}

void TransformPayload::identifyArduinoState(int state, Arduino::ARDUINO_STATE &newState) {
    switch (state) {
        case 0 :
            newState = Arduino::READY;
            break;
        case 1 :
            newState = Arduino::LIFT_ASC;
            break;
        case 2 :
            newState = Arduino::LIFT_DESC;
            break;
        case 3 :
            newState = Arduino::BIN_LOADING;
            break;
        case 4 :
            newState = Arduino::BIN_DUMPING;
            break;
        default:
            printf("\nUnknown state");
            break;
    }
}
