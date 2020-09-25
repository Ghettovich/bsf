#ifndef BSF_WEIGHTSENSORFORM_H
#define BSF_WEIGHTSENSORFORM_H

#include <domain/arduino.h>
#include <domain/weightcensor.h>
#include <QtWidgets/QWidget>

namespace Ui {
    class WeightSensorForm;
}

class WeightSensorForm : public QWidget {

    Q_OBJECT

public:
    WeightSensorForm(QWidget *, const Qt::WindowFlags &f, WeightSensor&);
    void updateWeightSensorForm(WeightSensor&, Arduino::ARDUINO_STATE);
    virtual ~WeightSensorForm();

public slots:
    void onUpdateDigitalDisplayWeight(int weight);

private:
    WeightSensor &weightSensor;
    int displayedComponentId = 0;
    Ui::WeightSensorForm *ui = nullptr;


};

#endif //BSF_WEIGHTSENSORFORM_H
