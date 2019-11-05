#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtCore/QString>

struct arduino {
    QString desc;
    QString ipAddress;
    QString name;

    qint16 port;
    int id;
};

#endif // ARDUINO_H

