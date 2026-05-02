//
// Created by Hashm A on 2026-04-19.
//

#ifndef DRAGY_CPP_MASTERCONTROLLER_H
#define DRAGY_CPP_MASTERCONTROLLER_H

#include "GPSController.h"
#include "InputController.h"
#include "ViewController.h"
#include "RunController.h"

#include "state.h"

class MasterController {
    AppState & app_state;

    GPSController gps_controller;
    InputController input_controller;
    ViewController view_controller;
    RunController run_controller;

    unsigned long previousFrameTime{};

public:
    MasterController(AppState & tracked_app_state);
    void Update();
};

#endif //DRAGY_CPP_MASTERCONTROLLER_H
