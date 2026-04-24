//
// Created by Hashm A on 2026-04-19.
//

#ifndef DRAGY_CPP_VIEWCONTROLLER_H
#define DRAGY_CPP_VIEWCONTROLLER_H

#include <state.h>

class ViewController {
    AppState * app_state;

public:
    ViewController(AppState * app_state_reference);
    void Draw();

    void displaySettings();

    void displayRollLastRun();

private:
    void displayDragLastRun();

    void displayLastRun();

    void displayBattery();

    void drawBackStage();

    void displaySpeedometer();

    void displayGPSWaitTime();

    void displaysSatelliteCount();

    void displayWelcome();

    void displayStaging();

    void displayRollTiming();

    void displayWaitingForStaging();

    void displayDragTiming();

    void displayTiming();
};

#endif //DRAGY_CPP_VIEWCONTROLLER_H
