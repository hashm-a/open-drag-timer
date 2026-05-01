//
// Created by Hashm A on 2026-04-19.
//

#ifndef DRAGY_CPP_VIEWCONTROLLER_H
#define DRAGY_CPP_VIEWCONTROLLER_H

#include <M5Unified.h>

#include "state.h"

class ViewController {
    AppState * app_state;
    M5Canvas display_buffer{};

public:
    ViewController(AppState * app_state_ptr);

    void Draw();

private:
    void displaySettings();

    void displayLastRollRun();

    void displayLastDragRun();

    void displayLastRun();

    void displayBattery();

    void drawBackStage();

    void displaySpeedometer();

    void displayGPSWaitTime();

    void displaysSatelliteCount();

    void displayWelcome();

    void displayStaging();

    void displayCurrentRollTiming();

    void displayWaitingForStaging();

    void displayCurrentDragTiming();

    void displayTiming();
};

#endif //DRAGY_CPP_VIEWCONTROLLER_H
