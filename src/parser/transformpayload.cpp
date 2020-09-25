#include "transformpayload.h"

void TransformPayload::updateArduinoWithPayload(int &_arduinoId, Arduino::ARDUINO_STATE &newState, QVector<IODevice *>& ioDeviceList, const QByteArray &payload) {
    auto parseError = new QJsonParseError;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));
    QJsonValue arduinoId (jsonDocument["arduinoId"].toInt());

    if (jsonDocument.isNull()) {
        printf("%s", "Failed to create JSON doc.\n");
        printf("error string %s", (char *)parseError->errorString().data());
    }
    if (!jsonDocument.isObject()) {
        printf("%s", "JSON is not an object.\n");
        printf("error string %s", (char *)parseError->errorString().data());
    }
    else {
        TransformPayload::ARDUINO_TYPE type;
        _arduinoId = arduinoId.toInt();
        identifyArduino(_arduinoId, type);

        if(type != ARDUINO_TYPE::UNKOWN) {
            QJsonValue state (jsonDocument["state"]);
            identifyArduinoState(state.toInt(), newState);

            // Parse io device items
            //parsePayload(jsonDocument, ioDeviceList, type);
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


void TransformPayload::identifyArduino(int arduinoId, ARDUINO_TYPE &type) {
    switch (arduinoId) {
        case ARDUINO_TYPE::BIN_LIFT :
            type = ARDUINO_TYPE::BIN_LIFT;
            break;
        case ARDUINO_TYPE::WEIGHT_STATION :
            type = ARDUINO_TYPE::WEIGHT_STATION;
        default:
            type = ARDUINO_TYPE::UNKOWN;
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
        case Arduino::RECIPE_SET:
            newState = Arduino::RECIPE_SET;
            break;
        case Arduino::RECIPE_TARGETS_MET:
            newState = Arduino::RECIPE_TARGETS_MET;
            break;
        default:
            printf("\nUnknown state");
            break;
    }
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

