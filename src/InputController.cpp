//
// Created by Hashm A on 2026-04-19.
//
#include <M5Unified.h>

#include "InputController.h"
#include "RunController.h"

#include "state.h"

InputController::InputController(AppState & tracked_app_state) : app_state(tracked_app_state) {}

void InputController::UpdateInput() {
    M5.update();
    readInput();
}

void InputController::readInput() {
    const m5::Button_Class & CONFIRM_BUTTON = M5.BtnA;
    const m5::Button_Class & LEFT_BUTTON = M5.BtnPWR;
    const m5::Button_Class & RIGHT_BUTTON = M5.BtnB;

    // DEBUG
    if (CONFIRM_BUTTON.wasPressed()) {
        app_state.gps.current_speed = 60;
        return;
    }
    // END DEBUG

    // Allow Sleeping While Charging
    if (!app_state.gps.IsReady()) {
        if (CONFIRM_BUTTON.wasDoubleClicked()) {
            M5.Power.powerOff();
        }

        return;
    }

    switch (app_state.stage) {
        case WELCOME: {
            if (RIGHT_BUTTON.wasClicked()) {
                app_state.SetStage(WAITING_FOR_STAGING);
                break;
            }
            if (LEFT_BUTTON.wasClicked()) {
                app_state.SetStage(SETTINGS);
                break;
            }
            break;
        }

        case VIEW_LAST_RUN: {
            if (RIGHT_BUTTON.wasClicked()) {
                app_state.SetStage(WAITING_FOR_STAGING);
                break;
            }
            if (LEFT_BUTTON.wasClicked()) {
                app_state.SetStage(SETTINGS);
                break;
            }
            break;
        }

        case SETTINGS: {
            switch (app_state.settings_state) {
                case SELECTING_RUN_TYPE: {
                    if (RIGHT_BUTTON.wasClicked() || LEFT_BUTTON.wasClicked()) { // We can get away with both right & left btn doing the same thing as there are only two options so it wraps around
                        app_state.NextRunMode();
                    } else if (CONFIRM_BUTTON.wasClicked()) {
                        if (app_state.run_mode == ROLL) {
                            app_state.settings_state = MODIFYING_ROLL_START;
                        } else {
                            app_state.settings_state = SELECTING_RUN_TYPE;
                            app_state.SetStage(VIEW_LAST_RUN);
                        }
                    }
                    break;
                }
                case MODIFYING_ROLL_START: {
                    if (LEFT_BUTTON.wasClicked()) {
                        if (app_state.settings_roll_params.x > 10) {
                            app_state.settings_roll_params.x -= 10;
                        }
                    } else if (RIGHT_BUTTON.wasClicked()) {
                        app_state.settings_roll_params.x += 10;
                    } else if (CONFIRM_BUTTON.wasClicked()) {
                        app_state.settings_state = MODIFYING_ROLL_END;
                    }
                    break;
                }
                case MODIFYING_ROLL_END: {
                    if (LEFT_BUTTON.wasClicked()) {
                        if (app_state.settings_roll_params.y > app_state.settings_roll_params.x + 20) {
                            app_state.settings_roll_params.y -= 10;
                        }
                    } else if (RIGHT_BUTTON.wasClicked()) {
                        app_state.settings_roll_params.y += 10;
                    } else if (CONFIRM_BUTTON.wasClicked()) {
                        app_state.settings_state = SELECTING_RUN_TYPE;
                        app_state.global_objects.run_controller->SetRoll(app_state.settings_roll_params.x, app_state.settings_roll_params.y);
                        app_state.SetStage(VIEW_LAST_RUN);
                    }
                    break;
                }
            }
            break;
        }

        case WAITING_FOR_STAGING: {
            if (RIGHT_BUTTON.wasClicked()) {
                app_state.SetStage(VIEW_LAST_RUN);
                break;
            }
            break;
        }

        case STAGING: {
            if (RIGHT_BUTTON.wasClicked()) {
                app_state.SetStage(VIEW_LAST_RUN);
                break;
            }
            break;
        }

        case TIMING: {
            if (RIGHT_BUTTON.wasClicked()) {
                app_state.global_objects.run_controller->EndCurrentRunPrematurely(); // Sets stage for us
                break;
            }
            break;
        }

        default:
            break;
    }
}
