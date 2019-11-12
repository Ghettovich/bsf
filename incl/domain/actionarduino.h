#ifndef BSF_ACTIONARDUINO_H
#define BSF_ACTIONARDUINO_H

#include <action.h>
#include <arduino.h>

struct ArduinoAction {
    int id;
    Action action;
    Arduino arduinoDev;
};
#endif //BSF_ACTIONARDUINO_H
