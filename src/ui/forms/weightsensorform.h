#ifndef BSF_WEIGHTSENSORFORM_H
#define BSF_WEIGHTSENSORFORM_H

#include <QtWidgets/QWidget>
#include <domain/weightcensor.h>

namespace Ui {
    class WeightSensorForm;
}

class WeightSensorForm : public QWidget {

    Q_OBJECT

public:
    WeightSensorForm(QWidget *, const Qt::WindowFlags &f, WeightCensor&);
    virtual ~WeightSensorForm();

public slots:
    void onUpdateDigitalDisplayWeight(int componentId, int weight);

private:
    WeightCensor &weightCensor;
    Ui::WeightSensorForm *ui = nullptr;

};

#endif //BSF_WEIGHTSENSORFORM_H
