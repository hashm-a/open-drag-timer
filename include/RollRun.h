//
// Created by Hashm A on 2026-04-20.
//

#ifndef DRAGY_CPP_ROLLRUN_H
#define DRAGY_CPP_ROLLRUN_H

#include <string>

#include "RunInterface.h"

class RollTarget : public RunInterface {
public:
    // RT specific
    float start_speed;
    float end_speed;

    RollTarget() : start_speed(100), end_speed(200) {
        name = std::string(std::to_string(static_cast<int>(start_speed)) + "-" + std::to_string(static_cast<int>(end_speed)));
    }

    RollTarget(const float start_speed, const float end_speed)
        : start_speed(start_speed),
          end_speed(end_speed) {

        name = std::string(std::to_string(static_cast<int>(start_speed)) + "-" + std::to_string(static_cast<int>(end_speed)));
    }

    void UpdateRunData(AppState * app_state) override {
        if (is_completed) {return;}
        if (app_state->gps.current_speed >= end_speed) {
            CompleteRunTarget(app_state);
        }
    }
};

#endif //DRAGY_CPP_ROLLRUN_H
