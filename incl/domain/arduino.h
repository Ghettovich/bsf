#ifndef BSF_ARDUINO_H
#define BSF_ARDUINO_H

#include <QtCore/QString>

struct Arduino {
    QString desc;
    QString ipAddress;
    QString name;

    qint16 port;
    int id;
};
#endif //BSF_ARDUINO_H
