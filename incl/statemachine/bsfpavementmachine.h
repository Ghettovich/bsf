#ifndef BSF_BSFPAVEMENTMACHINE_H
#define BSF_BSFPAVEMENTMACHINE_H

#include <incl/statemachine/events/recipedata.h>
#include <incl/statemachine/events/iodevicedata.h>
#include <incl/statemachine/events/recipeinfo.h>
#include "statemachine.h"
#include "pavementstateobject.h"

// BSF Statemachine class
class BsfPavementMachine : public StateMachine {
public:
    BsfPavementMachine() : StateMachine(ST_MAX_STATES) {};

    //Setters
    void setPavementRecipe(RecipeInfoData *);

    // external events taken by this state machine
    void halt();
    void setWeight(RecipeData *);

private:
    PavementStateObject *stateObject = new PavementStateObject();

    // state enumeration order must match the order of state
    // method entries in the state map
    enum E_States {
        ST_IDLE = 0,
        ST_STOP,
        ST_START,
        ST_CHANGE_WEIGHT,
        ST_BIN_LOADED,
        ST_MAX_STATES
    };

    // state machine state functions
//    void ST_Idle(EventData *);
//    void ST_Stop(EventData *);
//    void ST_Start(RecipeData *);
//    void ST_ChangeWeight(RecipeData *);
    STATE_DECLARE(BsfPavementMachine, Idle, RecipeInfoData);
    STATE_DECLARE(BsfPavementMachine, Stop, NoEventData);
    STATE_DECLARE(BsfPavementMachine, Start, NoEventData);
    STATE_DECLARE(BsfPavementMachine, ChangeWeight, RecipeData);
    STATE_DECLARE(BsfPavementMachine, BinLoaded, NoEventData);

    // state map to define state function order
    BEGIN_STATE_MAP
        STATE_MAP_ENTRY(&Idle)
        STATE_MAP_ENTRY(&Stop)
        STATE_MAP_ENTRY(&Start)
        STATE_MAP_ENTRY(&ChangeWeight)
        STATE_MAP_ENTRY(&BinLoaded)
    END_STATE_MAP


};

#endif //BSF_BSFPAVEMENTMACHINE_H
