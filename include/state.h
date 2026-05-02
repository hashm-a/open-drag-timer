//
// Created by Hashm A on 2026-04-20.
//

#ifndef DRAGY_CPP_STATE_H
#define DRAGY_CPP_STATE_H

#include "types.h"
#include "constants.h"

enum Stage {
    GPS_WAIT,
    WELCOME,
    SETTINGS,
    VIEW_LAST_RUN,
    WAITING_FOR_STAGING,
    STAGING,
    TIMING,
};

enum RunMode {
    DRAG,
    ROLL,
    COUNT,
};

struct GPSData {
    double current_speed{};
    double current_HDOP{};
    uint32_t satellite_count{};
    Vector2 location{};
    double altitude{};

    bool IsReady() const {
        return satellite_count>0;
    }
};

class RunController;

struct GlobalObjects {
    RunController * run_controller = nullptr;
};

enum SettingsState {
    SELECTING_RUN_TYPE,
    MODIFYING_ROLL_START,
    MODIFYING_ROLL_END
};

struct AppState {
    Stage stage{GPS_WAIT};
    GPSData gps;
    RunMode run_mode{DRAG};
    GlobalObjects global_objects;

    SettingsState settings_state{SELECTING_RUN_TYPE};
    Vector2 settings_roll_params{DEFAULT_ROLL_START,DEFAULT_ROLL_END};

    bool last_run_exists = false;

    void SetRunController(RunController * controller) {
        global_objects.run_controller = controller;
    }

    void NextRunMode() {
        run_mode = static_cast<RunMode>(static_cast<int>(run_mode) + 1);
        if (run_mode == COUNT) {
            run_mode = static_cast<RunMode>(0);
        }
    }

    void SetStage(const Stage new_stage) {
        switch (new_stage) {
            case GPS_WAIT:
                this->stage = GPS_WAIT;
                break;
            case WELCOME:
                this->stage = WELCOME;
                break;
            case SETTINGS:
                this->stage = SETTINGS;
                break;
            case VIEW_LAST_RUN:
                if (last_run_exists) {
                    this->stage = VIEW_LAST_RUN;
                } else {
                    this->stage = WELCOME;
                }
                break;
            case WAITING_FOR_STAGING:
                this->stage = WAITING_FOR_STAGING;
                break;
            case STAGING:
                this->stage = STAGING;
                break;
            case TIMING:
                this->stage = TIMING;
                break;
        }
    }
};

#endif //DRAGY_CPP_STATE_H
