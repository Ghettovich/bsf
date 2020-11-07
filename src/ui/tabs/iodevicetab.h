#ifndef BSF_IODEVICETAB_H
#define BSF_IODEVICETAB_H

#include <forms/deviceactionform.h>
#include <forms/iodeviceform.h>
#include <networkservice.h>
#include <QtCore/QVector>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

class IODeviceTab : public QWidget
{
    Q_OBJECT

public:
    IODeviceTab(QWidget * parent, const Qt::WindowFlags &f);


public slots:
    void updateIODeviceTypes(int);

private:
    DeviceActionForm * devForm = nullptr;
    IODeviceForm * ioDevForm = nullptr;
    QHBoxLayout *hbox = nullptr;
    void createDeviceActionForm();
    void createIODeviceForm();
};
#endif // BSF_IODEVICESTAB_H
