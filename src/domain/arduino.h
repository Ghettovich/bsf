#ifndef BSF_ARDUINO_H
#define BSF_ARDUINO_H

#include <QtCore/QString>

class Arduino {

public:
    Arduino(int id = 0);

    int getId() const;
    QString getDesc() const;
    void setDesc(const QString &desc);
    QString getIpAddress() const;
    void setIpAddress(const QString &ipAddress);
    QString getName() const;
    void setName(const QString &name);
    qint16 getPort() const;
    void setPort(qint16 port);

private:
    int id;
    QString desc;
    QString ipAddress;
    QString name;
    qint16 port;

};
#endif //BSF_ARDUINO_H
