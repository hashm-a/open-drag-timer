//
// Created by Hashm A on 2026-04-19.
//

#ifndef DRAGY_CPP_INPUTCONTROLLER_H
#define DRAGY_CPP_INPUTCONTROLLER_H

#include "state.h"

class InputController {
    AppState * app_state;

public:
    InputController(AppState * app_state_reference);
    void UpdateInput();

private:
    void readInput();
};

#endif //DRAGY_CPP_INPUTCONTROLLER_H
