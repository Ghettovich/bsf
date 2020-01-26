#include "transformpayload.h"

QList<IODeviceDTO *> TransformPayload::transformJSONPayloadToDtoIODeviceList(const QByteArray& byteArray) {
    QList<IODeviceDTO *> ioDeviceDTOList;
    auto * parseError = new QJsonParseError;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(byteArray));
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
        for (int ioDeviceIndex = 0; ioDeviceIndex < items.size(); ioDeviceIndex++) {
            QJsonObject ioDeviceObject = items[ioDeviceIndex].toObject();
            if (ioDeviceObject.contains("id")) {
                auto *ioDeviceDTO = new IODeviceDTO;
                int id = ioDeviceObject["id"].toInt();

                ioDeviceDTO->id = id;
                ioDeviceDTO->actionId = ioDeviceObject["actionId"].toInt();
                ioDeviceDTO->typeId = ioDeviceObject["typeId"].toInt();
                ioDeviceDTO->low = ioDeviceObject["low"].toInt();
                ioDeviceDTOList.append(ioDeviceDTO);
            }
        }
    }

    return ioDeviceDTOList;
}

ArduinoDTO TransformPayload::transformJSONPayloadToArduinoDto(const QByteArray &payload) {
    ArduinoDTO arduinoDto = ArduinoDTO();
    QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));

    arduinoDto.arduinoId = jsonDocument["arduinoId"].toInt();
    arduinoDto.recipeId = jsonDocument["recipeId"].toInt();
    arduinoDto.state = jsonDocument["state"].toInt();
    arduinoDto.stateReply = jsonDocument["stateReply"].toInt();
    arduinoDto.deviceId = jsonDocument["deviceId"].toInt();
    arduinoDto.componentId = jsonDocument["componentId"].toInt();
    arduinoDto.weight = jsonDocument["weight"].toInt();

    return arduinoDto;
}

QList<IODeviceDTO *> TransformPayload::transformPayloadToDtoIODeviceList(const QByteArray& byteArray) {
    int i = 0, j = 1;
    QString part = "";
    bool shouldConvert = false;
    auto * ioDeviceDto = new IODeviceDTO();
    QList<IODeviceDTO *> ioDeviceDTOList;

    for(QChar c: byteArray) {

        if(c.isSpace() || (j == byteArray.size())) {
            // hit EOL, add last part
            i = 0;
            // add last value and clear part
            ioDeviceDto->low = part.toInt() == 1;
            part.clear();
            // add to list
            ioDeviceDTOList.append(ioDeviceDto);
            ioDeviceDto = new IODeviceDTO();
            //qInfo() << "hit space";
        }
        else if (c == ',') {
            //qInfo() << "hit splitter, set convert true";
            shouldConvert = true;
        }
        if (shouldConvert) {
            //qInfo() << "converted = " << part;
            switch (i) {
                case 0 :
                    ioDeviceDto->id = part.toInt();
                    break;
                case 1 :
                    ioDeviceDto->actionId = part.toInt();;
                    break;
                case 2 :
                    ioDeviceDto->typeId = part.toInt();;
                    break;
                default:
                    break;
            }
            i++;
            part.clear();
            shouldConvert = false;
        }
        if (c.isDigit()) {
            part.append(c);
            //qInfo() << "append to string";
        }
        j++;
    }
    return ioDeviceDTOList;
}

IODeviceDTO *TransformPayload::transformJSONPayloadToIODevice(int id, const QByteArray& byteArray) {
    auto ioDeviceDTO = new IODeviceDTO;
    QJsonObject ioDeviceObject;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(byteArray.data()));
    QJsonObject jsonObject(jsonDocument["iodevices"].toObject());
    QJsonArray items = jsonObject["items"].toArray();

    printf("%s", byteArray.data());

    if (jsonDocument.isNull()) {
        printf("%s", "Failed to create JSON doc.");
    }
    if (!jsonDocument.isObject()) {
        printf("%s", "JSON is not an object.");
    }
    else {
        for (int ioDeviceIndex = 0; ioDeviceIndex < items.size(); ioDeviceIndex++) {
            ioDeviceObject = items[ioDeviceIndex].toObject();
            printf("%s", "entered loop");
            if (ioDeviceObject.contains("id") && ioDeviceObject["id"].toInt() == id) {
                printf("%s %d", "found id!", id);
                ioDeviceDTO->id = id;
                ioDeviceDTO->actionId = ioDeviceObject["actionId"].toInt();
                ioDeviceDTO->typeId = ioDeviceObject["typeId"].toInt();
                ioDeviceDTO->low = ioDeviceObject["low"].toInt();
            }
        }
    }

    return ioDeviceDTO;
}

QVector<IODevice *> TransformPayload::transformPayloadToIODeviceList(const QByteArray &payload) {
    QVector<IODevice *> ioDeviceDTOList;
    auto parseError = new QJsonParseError;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));
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
        parseIODeviceItemsInPayload(items, ioDeviceDTOList);
    }

    return ioDeviceDTOList;
}
void TransformPayload::parseIODeviceItemsInPayload(QJsonArray &items, QVector<IODevice *> &ioDeviceList) {

    for (int ioDeviceIndex = 0; ioDeviceIndex < items.size(); ioDeviceIndex++) {
        QJsonObject ioDeviceObject = items[ioDeviceIndex].toObject();
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
            printf("\nAdded iodevice from payload");
        }
    }
}
