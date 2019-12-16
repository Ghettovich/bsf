#ifndef BSF_WEIGHTSENSORFORM_H
#define BSF_WEIGHTSENSORFORM_H

#include <QtWidgets/QWidget>
#include <incl/domain/iodevice.h>

namespace Ui {
    class WeightSensorForm;
}

class WeightSensorForm : public QWidget {

    Q_OBJECT

public:
    explicit WeightSensorForm(QWidget *parent = nullptr, IODevice *_ioDevice = nullptr);
    virtual ~WeightSensorForm();

private:
    IODevice *ioDevice = nullptr;
    Ui::WeightSensorForm *ui = nullptr;

public slots:
    void setIODeviceState(IODeviceState state);
};

#endif //BSF_WEIGHTSENSORFORM_H
