#include <incl/statemachine/bsfpavementmachine.h>

void BsfPavementMachine::halt() {
    // given the Halt event, transition to a new state based upon
    // the current state of the state machine
    BEGIN_TRANSITION_MAP                      // - Current State -
            TRANSITION_MAP_ENTRY (EVENT_IGNORED)  // ST_Idle
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)  // ST_Stop
            TRANSITION_MAP_ENTRY (ST_STOP)        // ST_Start
            TRANSITION_MAP_ENTRY (ST_STOP)        // ST_ChangeSpeed
    END_TRANSITION_MAP(nullptr)
}

void BsfPavementMachine::setWeight(RecipeData *pData) {
    BEGIN_TRANSITION_MAP                      // - Current State -
            TRANSITION_MAP_ENTRY (ST_START)       // ST_Idle
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)  // ST_Stop
            TRANSITION_MAP_ENTRY (ST_CHANGE_WEIGHT)// ST_Start
            TRANSITION_MAP_ENTRY (ST_CHANGE_WEIGHT)// ST_ChangeSpeed
    END_TRANSITION_MAP(pData)
}

void BsfPavementMachine::ST_Idle(EventData * pData) {
    printf("\n%s", "Motor::ST_Idle");

}

void BsfPavementMachine::ST_Stop(EventData *pData) {
    printf("\n%s", "Motor::ST_Stop");

    stateObject->recipe->setPlastifier(0);
    InternalEvent(ST_IDLE);
}

void BsfPavementMachine::ST_Start(RecipeData *pData) {
    printf("\n%s", "Motor::ST_Start");
    stateObject->recipe->setPlastifier(0);
}

void BsfPavementMachine::ST_ChangeWeight(RecipeData *pData) {

    if(pData->id == 1) {
        stateObject->recipe->setPlastifier(stateObject->recipe->getPlastifier() + pData->weight);
        printf("%s \ncurrent weight = %d", "Motor::ST_ChangeWeight", stateObject->recipe->getPlastifier());
    }

    if(stateObject->recipe->isPlastifierTargetMet(target)) {
        printf("\nmet target should transition");
        InternalEvent(ST_STOP);
    }
    else {
        printf("\ntarget not met");
    }
}
