#include "ui_devicewidget.h"

#ifndef BSF_DEVICEFORM_H
#define BSF_DEVICEFORM_H

#endif //BSF_DEVICEFORM_H

namespace Ui {
    class DeviceForm;
}

class DeviceForm : public QWidget
{
public:
    explicit DeviceForm(QWidget *parent = nullptr);

private:
    Ui::bsfDeviceWidget ui;
};