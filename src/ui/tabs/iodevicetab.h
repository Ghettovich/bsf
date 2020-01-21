#ifndef BSF_IODEVICETAB_H
#define BSF_IODEVICETAB_H

#include <service/iodeviceservice.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

class IODeviceTab : public QWidget
{
    Q_OBJECT

public:
    IODeviceTab(QWidget * parent);

private:
    IODeviceService ioDeviceService;
    QHBoxLayout *hbox = nullptr;
};
#endif // BSF_IODEVICESTAB_H
