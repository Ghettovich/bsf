#ifndef BSF_WEIGHTSENSORFORM_H
#define BSF_WEIGHTSENSORFORM_H


#include <incl/domain/iodevice.h>

namespace Ui {
    class WeightSensorForm;
}

class WeightSensorForm : public QWidget {

public:
    explicit WeightSensorForm(QWidget *parent = nullptr, IODevice *_ioDevice = nullptr);
    virtual ~WeightSensorForm();

private:
    IODevice *ioDevice = nullptr;
    Ui::WeightSensorForm *ui = nullptr;
};

#endif //BSF_WEIGHTSENSORFORM_H
