#ifndef BSF_ARDUINO_H
#define BSF_ARDUINO_H

#include "iodevice.h"
#include <QObject>
#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QUrl>

class Arduino {

    Q_GADGET

public:
    enum ARDUINO_STATE {
        UNKOWN, READY, LIFT_ASC, LIFT_DESC, BIN_LOADING, BIN_DUMPING
    };
    Q_ENUM(ARDUINO_STATE);

    explicit Arduino(int id = 0);

    int getId() const;
    QString getDesc() const;
    void setDesc(const QString &);
    QString getIpAddress() const;
    void setIpAddress(const QString &);
    QString getName() const;
    void setName(const QString &);
    qint16 getPort() const;
    void setPort(qint16 port);
    void addIODevice(IODevice *);
    QString getStatusMessage() const;
    void setStatusMessage(const QString &);
    ARDUINO_STATE getArduinoState();
    void setArduinoState(ARDUINO_STATE);
    QVector<IODevice *> getIoDeviceList();
    bool hasRelayIODevices();
    bool hasWeightSensorIODevices();
    bool hasDetectionSensorIODevices();
    void updateIODeviceList(const QVector<IODevice *>&);
    QUrl generateQUrl(const QString& location = "");

private:
    int id;
    qint16 port = 0;
    QString desc;
    QString ipAddress;
    QString name;
    QString statusMessage;
    ARDUINO_STATE arduinoState;
    QVector<IODevice *> ioDeviceList;
};

#endif //BSF_ARDUINO_H
