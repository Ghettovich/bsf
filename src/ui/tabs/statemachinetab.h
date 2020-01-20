#ifndef BSF_STATEMACHINETAB_H
#define BSF_STATEMACHINETAB_H

#include <domain/recipe.h>
#include <domain/iodevice.h>
#include <domain/weightcensor.h>

#include <service/payloadservice.h>
#include <statemachine/bsfpavementmachine.h>
#include <ui/forms/detectionsensorform.h>
#include <ui/forms/weightsensorform.h>
#include <ui/forms/relayform.h>

#include <QtCore/QList>
#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>

class StateMachineTab : public QWidget {

    Q_OBJECT

public:
    explicit StateMachineTab();

private:
    int arduinoFeederAndLiftId = 1, arduinoWeightStationId = 2;
    int loadCellId = 1, sensorLiftDropId = 5, sensorLiftLoadId = 6, relayLiftUpId = 7, relayLiftDownId = 8;
    PayloadService payloadService;
    Recipe *selectedRecipe = nullptr;
    QList<Recipe *> recipeList;
    QList<IODevice *> ioDeviceList;
    QList<IODevice *> ioDeviceWeightStationList;
    QList<WeightCensor *> weightSensorList;
    BsfPavementMachine *pavementMachine;

    QHBoxLayout *hbox = nullptr;

    QComboBox * comboBoxRecipe = nullptr;
    QGroupBox * grpboxSelectRecipe = nullptr;
    DetectionSensorForm *binLoadedDetectionSensorForm = nullptr;
    RelayForm *relayFormLiftDown = nullptr;
    QPushButton *btnStart = nullptr;

    QGroupBox * grpboxBinLoading = nullptr;
    RelayForm *relayFormLiftUp = nullptr;
    WeightSensorForm *weightSensorForm = nullptr;
    DetectionSensorForm *binDropDetectionSensorForm = nullptr;

    void fillRecipeComboBox();
    void createSelectRecipeGroupBox();
    void createBinLoadGroupBox();
    void createIODeviceForms();

public slots:
    void onClickStart();
    void onSelectRecipeCombobox(int comboBoxItemId);
    void onReceiveFoundWeightStation(const QByteArray &);

};
#endif //BSF_STATEMACHINETAB_H
