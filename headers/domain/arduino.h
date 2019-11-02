#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtCore/QString>

class ArduinoDevice {

public:
    void setName(QString name);
    QString getName();

    QString getIpAddress();
    void setIpAddress(QString value);

    qint16 getPort();
    void setPort(qint16 port);

    QString getDescription();
    void setDescription(QString description);

private:
    QString name = nullptr;
    QString ipAddress = nullptr;
    qint16 port = 0;
    QString description = nullptr;
};

#endif // ARDUINO_H

