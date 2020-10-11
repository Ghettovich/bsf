#ifndef BSF_WEIGHTSENSORFORM_H
#define BSF_WEIGHTSENSORFORM_H

#include <domain/arduino.h>
#include <domain/weightcensor.h>
#include <QtWidgets/QWidget>
#include <ui/model/tablecomponentmodel.h>

namespace Ui {
    class WeightSensorForm;
}

class WeightSensorForm : public QWidget {

    Q_OBJECT

public:
    WeightSensorForm(QWidget *, const Qt::WindowFlags &f, WeightSensor&);
    void updateWeightSensorForm(WeightSensor&, Arduino::ARDUINO_STATE);
    void initRecipeComboBox();
    void updateTargetsInTableView();
    void updateTargetInfo();
    virtual ~WeightSensorForm();

public slots:
    void onUpdateDigitalDisplayWeight(int weight);
    void onRecipeComboBoxIndexChanged(int);
    void onClickSetSetRecipe();

private:
    Recipe currentRecipe;
    WeightSensor &weightSensor;
    QVector<Recipe> recipeList;
    Component::COMPONENT selectedComponent;
    TableComponentModel *componentTableModel = nullptr;
    Ui::WeightSensorForm *ui = nullptr;

    void populateTableWithComponents();

signals:
    void broadcastRecipe(Recipe);
};

#endif //BSF_WEIGHTSENSORFORM_H
