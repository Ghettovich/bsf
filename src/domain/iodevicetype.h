#ifndef BSF_IODEVICETYPE_H
#define BSF_IODEVICETYPE_H

#include <QObject>
#include <QString>

class IODeviceType {

    Q_GADGET;

public:
    enum IO_DEVICE_TYPE { UNKOWN, WEIGHTSENSOR, DETECTIONSENSOR, RELAY };
    Q_ENUM(IO_DEVICE_TYPE);

    IODeviceType(int id = 0);
    int getId() const;
    QString getType() const;
    void setType(const QString&);
    QString getDescription() const;
    void setDescription(const QString&);
    IO_DEVICE_TYPE getIODeviceType();
    void setIODeviceType(IO_DEVICE_TYPE);

private:
    int id;
    QString type;
    QString description;
    IO_DEVICE_TYPE ioDeviceType;
};

#endif //BSF_IODEVICETYPE_H
