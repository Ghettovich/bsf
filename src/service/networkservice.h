#ifndef BSF_NETWORKSERVICE_H
#define BSF_NETWORKSERVICE_H


#include <iodevice.h>
#include <arduino.h>
#include <transformpayload.h>
#include <requestmanager/requestmanager.h>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QVector>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <socketmanager/socketclient.h>
#include <socketmanager/tcpserver.h>

class NetworkService : public QObject {

    Q_OBJECT

private:
    Arduino arduino;
    SocketClient client;
    LocalTcpServer tcpServer;
    TransformPayload transformPayload;

public:
    explicit NetworkService(QObject *parent);
    void requestPayload(const Arduino &arduino);
    void toggleRelay(const Arduino &_arduino, int relayId);
    void setRecipeForWeightstation(const Arduino &_arduino, const Recipe &recipe);

public slots:
    void onTcpReply(const QByteArray &data);
    void onReceiveRequestError(QNetworkReply::NetworkError);
    void onParseSucces(int arduinoId,
                       TransformPayload::ARDUINO_TYPE type,
                       Arduino::ARDUINO_STATE state,
                       QJsonDocument& jsonDocument);

signals:
    void failedToParseJson();
    void parsedJson(int arduinoId,
                    TransformPayload::ARDUINO_TYPE type,
                    Arduino::ARDUINO_STATE state,
                    QJsonDocument& jsonDocument);
    void receivedUpdateForWeightSensor(IODevice*, Arduino::ARDUINO_STATE);
    void sendArduinoWithNewStates(int, Arduino::ARDUINO_STATE, const QVector<IODevice *>&);
};


#endif //BSF_NETWORKSERVICE_H
