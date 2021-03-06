#ifndef BSF_TRANSFORMPAYLOAD_H
#define BSF_TRANSFORMPAYLOAD_H

#include <arduino.h>
#include <detectionsensor.h>
#include <relay.h>
#include <weightcensor.h>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class TransformPayload : public QObject {

    Q_OBJECT

public:
    enum ARDUINO_TYPE {
        UNKOWN = 0, BIN_LIFT = 1, WEIGHT_STATION = 2
    };
    Q_ENUM(ARDUINO_TYPE);

    void updateArduinoWithPayload(int&, Arduino::ARDUINO_STATE&, QVector<IODevice *>&, const QByteArray&);
    ARDUINO_TYPE identifyArduinoWithId(int arduinoId);
    Arduino::ARDUINO_STATE identifyArduinoState(int state);
    void parseIODeviceItemsInPayload(QJsonDocument &, QVector<IODevice *>&);
    bool validateJsonDocument(QJsonDocument&, QString &errorMsg);
    IODevice *parseItemWeightStation(QJsonDocument&);
    Recipe addRecipeComponents(QJsonDocument &jsonDocument);
    Component::COMPONENT identifyComponent(int component);
};
#endif //BSF_TRANSFORMPAYLOAD_H
