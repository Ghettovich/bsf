#include "transformpayload.h"

void TransformPayload::updateArduinoWithPayload(int &_arduinoId, Arduino::ARDUINO_STATE &newState, QVector<IODevice *>& ioDeviceList, const QByteArray &payload) {
    QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));
    QJsonValue arduinoId (jsonDocument["arduinoId"].toInt());

    if (validateJsonDocument(jsonDocument)) {
        _arduinoId = arduinoId.toInt();
        TransformPayload::ARDUINO_TYPE type = identifyArduinoWithId(_arduinoId);

        if(type != ARDUINO_TYPE::UNKOWN) {
            QJsonValue state (jsonDocument["state"]);
            newState = identifyArduinoState(state.toInt());

            // Parse io device items
            parseIODeviceItemsInPayload(jsonDocument, ioDeviceList);
        }
    }
}
/*
 * Parse a json document to an IODevice vector list.
 * Both detection sensor and relay are LOW when power is on. e.g. When the detectionsensors is able to
 * see the bin they are LOW. When power flows through the relay they are LOW.
 * Weightsensors are digital. When HIGH it means they are active and a recipe is in progress.
 * */
void TransformPayload::parseIODeviceItemsInPayload(QJsonDocument &jsonDocument, QVector<IODevice *> &ioDeviceList) {
    QJsonObject jsonObject(jsonDocument["iodevices"].toObject());
    QJsonArray items = jsonObject["items"].toArray();

    for (int i = 0; i < items.size(); i++) {
        QJsonObject ioDeviceObject = items[i].toObject();
        if (ioDeviceObject.contains("id")) {

            if(ioDeviceObject["typeId"].toInt() == 1) {
                auto weightSensor = new WeightSensor(ioDeviceObject["id"].toInt()
                        , ioDeviceObject["low"].toInt() == 0 ? IODevice::HIGH : IODevice::LOW);
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

IODevice *TransformPayload::parseItemWeightStation(QJsonDocument &jsonDocument) {
    IODevice *ioDevice;
    QJsonValue iodeviceId(jsonDocument["iodeviceId"]);
    QJsonValue jsonValueLow(jsonDocument["low"]);

    QJsonValue recipeId(jsonDocument["recipeId"]);
    Recipe recipe(recipeId.toInt());

    QJsonArray jsonArray(jsonDocument["components"].toArray());

    if(jsonDocument["typeId"].toInt() == IODeviceType::WEIGHTSENSOR) {

        // REMEMBER!! scale is DIGITAL input, HIGH means ON and LOW if OFF
        IODevice::IO_DEVICE_HIGH_LOW low = jsonValueLow.toInt() == 0 ? IODevice::LOW : IODevice::HIGH;
        ioDevice =  new WeightSensor(iodeviceId.toInt(), recipe, low);

        for (auto && i : jsonArray) {
            QJsonObject ioDeviceObject = i.toObject();

            if (ioDeviceObject.contains("id")) {
                Component comp(ioDeviceObject["id"].toInt());
                comp.setTargetWeight(ioDeviceObject["weight"].toInt());
                 recipe.componentList.append(comp);
            }
        }

        return ioDevice;
    }

    printf("Could not determine iodevice type");
    return nullptr;
}

bool TransformPayload::validateJsonDocument(QJsonDocument &jsonDocument) {
    auto parseError = new QJsonParseError;
    if (jsonDocument.isNull()) {
        printf("%s", "Failed to create JSON doc.\n");
        printf("error string %s", (char *)parseError->errorString().data());
        return false;
    }
    if (!jsonDocument.isObject()) {
        printf("%s", "JSON is not an object.\n");
        printf("error string %s", (char *)parseError->errorString().data());
        return false;
    }

    return true;
}

TransformPayload::ARDUINO_TYPE TransformPayload::identifyArduinoWithId(int arduinoId) {
    switch (arduinoId) {
        case ARDUINO_TYPE::BIN_LIFT :
            return ARDUINO_TYPE::BIN_LIFT;
        case ARDUINO_TYPE::WEIGHT_STATION :
            return ARDUINO_TYPE::WEIGHT_STATION;
        default:
            return ARDUINO_TYPE::UNKOWN;
    }
}

Arduino::ARDUINO_STATE TransformPayload::identifyArduinoState(int state) {
    switch (state) {
        case Arduino::READY :
            return Arduino::READY;
        case Arduino::LIFT_ASC :
            return Arduino::LIFT_ASC;
        case Arduino::LIFT_DESC :
            return Arduino::LIFT_DESC;
        case Arduino::BIN_LOADING :
            return Arduino::BIN_LOADING;
        case Arduino::BIN_DUMPING :
            return Arduino::BIN_DUMPING;
        case Arduino::RECIPE_SET :
            return Arduino::RECIPE_SET;
        case Arduino::RECIPE_TARGETS_MET :
            return Arduino::RECIPE_TARGETS_MET;
        default:
            return Arduino::UNKOWN;
    }
}

