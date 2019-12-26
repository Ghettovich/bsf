#ifndef BSF_BSFPAVEMENTMACHINE_H
#define BSF_BSFPAVEMENTMACHINE_H

#include <incl/statemachine/events/recipedata.h>
#include "statemachine.h"
#include "pavementstateobject.h"

// BSF Statemachine class
class BsfPavementMachine : public StateMachine {
public:
    BsfPavementMachine() : StateMachine(ST_MAX_STATES) {};

    // external events taken by this state machine
    void halt();
    void setWeight(RecipeData *);

private:
    // ToDo: replace with state object
    PavementStateObject *stateObject = new PavementStateObject();
    int target = 5;

    // state machine state functions
    void ST_Idle(EventData *);
    void ST_Stop(EventData *);
    void ST_Start(RecipeData *);
    void ST_ChangeWeight(RecipeData *);

    // state map to define state function order
    BEGIN_STATE_MAP
        STATE_MAP_ENTRY(&BsfPavementMachine::ST_Idle)
        STATE_MAP_ENTRY(&BsfPavementMachine::ST_Stop)
        STATE_MAP_ENTRY(&BsfPavementMachine::ST_Start)
        STATE_MAP_ENTRY(&BsfPavementMachine::ST_ChangeWeight)
    END_STATE_MAP

    // state enumeration order must match the order of state
    // method entries in the state map
    enum E_States {
        ST_IDLE = 0,
        ST_STOP,
        ST_START,
        ST_CHANGE_WEIGHT,
        ST_MAX_STATES
    };
};

#endif //BSF_BSFPAVEMENTMACHINE_H
