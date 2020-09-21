#include <statemachine/bsfpavementmachine.h>

void BsfPavementMachine::setPavementRecipe(RecipeInfoData *pData) {
    BEGIN_TRANSITION_MAP                      // - Current State -
            TRANSITION_MAP_ENTRY (ST_IDLE)          // ST_Idle
            TRANSITION_MAP_ENTRY (ST_STOP)          // ST_Stop
            TRANSITION_MAP_ENTRY (ST_START)         // ST_Start
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)    // ST_ChangeWeight
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)    // ST_BinLoaded
    END_TRANSITION_MAP(pData)
}

void BsfPavementMachine::setWeight(RecipeData *pData) {
    BEGIN_TRANSITION_MAP                      // - Current State -
            TRANSITION_MAP_ENTRY (EVENT_IGNORED)       // ST_Idle
            TRANSITION_MAP_ENTRY (ST_STOP)             // ST_Stop
            TRANSITION_MAP_ENTRY (ST_CHANGE_WEIGHT)       // ST_Start
            TRANSITION_MAP_ENTRY (ST_CHANGE_WEIGHT)    // ST_ChangeWeight
            TRANSITION_MAP_ENTRY (ST_BIN_LOADED)    // ST_BinLoaded
    END_TRANSITION_MAP(pData)
}

void BsfPavementMachine::halt() {
    // given the Halt event, transition to a new state based upon
    // the current state of the state machine
    BEGIN_TRANSITION_MAP                      // - Current State -
            TRANSITION_MAP_ENTRY (EVENT_IGNORED)  // ST_Idle
            TRANSITION_MAP_ENTRY (ST_STOP)  // ST_Stop
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)        // ST_Start
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)        // ST_ChangeWeight
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)        // ST_BinLoaded
    END_TRANSITION_MAP(nullptr)
}

STATE_DEFINE(BsfPavementMachine, Idle, RecipeInfoData) {
    printf("\n%s", "Motor::ST_Idle");
    stateObject->setRecipe(data->recipe);
    InternalEvent(ST_START);
}

STATE_DEFINE(BsfPavementMachine, Stop, NoEventData) {
    printf("\n%s", "Motor::ST_Stop");
    InternalEvent(ST_IDLE);
}

STATE_DEFINE(BsfPavementMachine, Start, NoEventData) {
    printf("\n%s", "Motor::ST_Start");
}

STATE_DEFINE(BsfPavementMachine, ChangeWeight, RecipeData) {
    printf("\n%s", "call to change weight...");
    if(data->id == 1) {
        stateObject->getRecipe().incrementCurrentWeightPlastifier(data->weight);
        printf("%s \ncurrent weight = %d", "Motor::ST_ChangeWeight", stateObject->getRecipe().getCurrentWeightPlastifier());
    }

    if(stateObject->getRecipe().isPlastifierTargetMet()) {
        printf("\nmet target should transition");
        InternalEvent(ST_BIN_LOADED);
    }
    else {
        printf("\ntarget not met");
    }
}

STATE_DEFINE(BsfPavementMachine, BinLoaded, NoEventData) {
    printf("\n%s", "Motor::BinLoaded, ready for lift asc");
}

QString BsfPavementMachine::stateMessage() {
    QString state;

    switch(GetCurrentState()) {
        case ST_IDLE :
            state = "Idle";
            break;
        case ST_STOP :
            state = "Stop";
            break;
        case ST_START :
            state = "Start";
            break;
        case ST_BIN_LOADED :
            state = "Bin loaded";
            break;
        default:
            break;
    }
    return state;
}

PavementStateObject *BsfPavementMachine::getStateObject() const {
    return stateObject;
}



