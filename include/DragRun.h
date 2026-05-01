//
// Created by Hashm A on 2026-04-20.
//

#ifndef DRAGY_CPP_DRAGRUN_H
#define DRAGY_CPP_DRAGRUN_H

#include "RunInterface.h"

#include "gpsmath.h"

class DragSpeedTarget : public RunInterface {
public:
    // DS specific
    float target_speed;

    DragSpeedTarget(const char *name, const float target_speed)
        : target_speed(target_speed) {
        this->name = name;
    }

    void UpdateRunData(AppState * app_state) override {
        if (is_completed) {return;}
        if (app_state->gps.current_speed >= target_speed) {
            CompleteRunTarget(app_state);
        }
    }
};

// ISSUE
class DragDistanceTarget : public RunInterface {
public:
    // DD specific
    float target_distance;

    // When launch set start pos
    DragDistanceTarget(const char * name, const float target_distance)
    : target_distance(target_distance) {
        this->name = name;
    }

    void UpdateRunData(AppState * app_state) override {
        if (is_completed) {return;}
        if (GetDistanceBetweenInKM(starting_position, app_state->gps.location) >= target_distance) {
            CompleteRunTarget(app_state);
        }
    }
};

#endif //DRAGY_CPP_DRAGRUN_H
