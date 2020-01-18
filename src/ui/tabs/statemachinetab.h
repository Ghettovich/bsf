#ifndef BSF_STATEMACHINETAB_H
#define BSF_STATEMACHINETAB_H

#include <QtWidgets/QTabWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <statemachine/bsfpavementmachine.h>
#include <repo/iodevicerepo.h>
#include <repo/reciperepo.h>
#include <service/payloadservice.h>
#include <ui/forms/detectionsensorform.h>
#include <ui/forms/relayform.h>
#include <ui/forms/weightsensorform.h>

class StateMachineTab : public QTabWidget {

    Q_OBJECT

public:
    explicit StateMachineTab(QWidget *parent = nullptr);

private:
    int arduinoFeederAndLiftId = 1, arduinoWeightStationId = 2;
    int loadCellId = 1, sensorLiftDropId = 5, sensorLiftLoadId = 6, relayLiftUpId = 7, relayLiftDownId = 8;
    PayloadService payloadService;
    Recipe *selectedRecipe = nullptr;
    QList<Recipe *> recipeList;
    QList<IODevice *> ioDeviceList;
    QList<IODevice *> ioDeviceWeightStationList;
    QList<WeightCensor *> weightSensorList;
    IODeviceRepository *ioDeviceRepository = nullptr;
    RecipeRepository * recipeRepository = nullptr;
    QComboBox *comboBoxRecipe = nullptr;
    BsfPavementMachine *pavementMachine;

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
