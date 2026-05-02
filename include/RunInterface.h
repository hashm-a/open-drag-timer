//
// Created by Hashm A on 2026-04-21.
//

#ifndef DRAGY_CPP_RUNINTERFACE_H
#define DRAGY_CPP_RUNINTERFACE_H

#include <Arduino.h>

#include "AudioController.h"

#include "state.h"
#include "types.h"

class RunInterface {
public:
    std::string name{};

    unsigned long start_time{};
    double starting_altitude{};
    Vector2 starting_position{};

    bool is_completed{};
    unsigned long time_at_completion{};
    double ending_altitude{};
    Vector2 ending_position{};

    virtual ~RunInterface() = default;
    virtual void UpdateRunData(AppState & app_state) = 0;

    void ResetRun() {
        start_time = {};
        starting_altitude = {};
        starting_position = {};
        is_completed = {};
        time_at_completion = {};
        ending_altitude = {};
        ending_position = {};
    }

    void Launch(const AppState & app_state) {
        ResetRun();

        start_time = millis();
        starting_altitude = app_state.gps.altitude;
        starting_position = app_state.gps.location;
    }

    void CompleteRunTarget(const AppState & app_state) {
        is_completed = true;
        time_at_completion = millis();
        ending_position = app_state.gps.location;
        ending_altitude = app_state.gps.altitude;

        AudioController::PlayBeep();
    }

    void EndRunTargetPremature() {
        if (!is_completed) {
            ResetRun();
        }
    }
};

#endif //DRAGY_CPP_RUNINTERFACE_H
