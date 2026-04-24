//
// Created by Hashm A on 2026-04-21.
//

#ifndef DRAGY_CPP_RUNINTERFACE_H
#define DRAGY_CPP_RUNINTERFACE_H
#include "state.h"
#include "types.h"
#include <Arduino.h>

#include "AudioController.h"

class RunInterface {
public:
    std::string name;
    unsigned long start_time;
    int starting_altitude;
    Vector2 starting_position{};

    bool is_completed = false;
    unsigned long time_at_completion;
    int ending_altitude;
    Vector2 ending_position{};

    virtual ~RunInterface() = default;
    virtual void UpdateRunData(AppState * app_state) = 0;

    void ResetRun() {
        start_time = 0;
        starting_altitude = 0;
        starting_position = {0,0};
        is_completed = false;
        time_at_completion = 0;
        ending_altitude = 0;
        ending_position = {0,0};
    }

    void Launch(AppState * app_state) {
        is_completed = false;
        start_time = millis();
        starting_altitude = app_state->gps.altitude;
        starting_position = app_state->gps.location;
    }

    void CompleteRunTarget(AppState * app_state) {
        is_completed = true;
        time_at_completion = millis();
        ending_position = app_state->gps.location;
        ending_altitude = app_state->gps.altitude;

        AudioController::PlayBeep();
    }

    void EndRunTargetPremature() {
        if (!is_completed) {
            ResetRun();
        }
    }
};

#endif //DRAGY_CPP_RUNINTERFACE_H
