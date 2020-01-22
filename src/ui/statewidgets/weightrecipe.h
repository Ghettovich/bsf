#ifndef BSF_WEIGHTRECIPE_H
#define BSF_WEIGHTRECIPE_H

#include <ui/forms/detectionsensorform.h>
#include <ui/forms/relayform.h>
#include <ui/forms/weightsensorform.h>
#include <statemachine/pavementstateobject.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>

class WeighRecipe : public QWidget {

    struct RecipeConf {
        int arduinoId = 2;
        int deviceIdArray[4] = {1, 5, 6, 7};
    };

public:
    WeighRecipe(QWidget *parent, const Qt::WindowFlags &f, PavementStateObject *_stateObject);

private:
    Recipe recipe;
    PavementStateObject * stateObject = nullptr;
    QHBoxLayout * hbox = nullptr;
    QGroupBox * grpboxBinLoading = nullptr;
    RelayForm *relayFormLiftUp = nullptr;
    WeightSensorForm *weightSensorForm = nullptr;
    DetectionSensorForm *binDropDetectionSensorForm = nullptr;

    void createBinLoadGroupBox();
};


#endif //BSF_WEIGHTRECIPE_H
