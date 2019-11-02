#include <QtWidgets/QWidget>
#include "deviceform.h"

DeviceForm::DeviceForm(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
    groupBoxArduino = ui.groupBoxDevice;

    lblName = ui.labelName;
    lblIpAddress = ui.labelIpAddress;
    lblPort = ui.labelPort;
    lblDescription = ui.labelDescription;

    lineEditName = ui.lineEditName;
    lineEditIpAddress = ui.lineEditIPAddress;
    lineEditNPort = ui.lineEditPort;

    plainTextEditDescription = ui.plainTextEditDescription;

}
