//
// Created by Hashm A on 2026-04-19.
//

#include "ViewController.h"

// #include <M5StickCPlus2.h>
#include <M5Unified.h>
#include <state.h>

#include "RunController.h"

ViewController::ViewController(AppState * app_state_ptr) : app_state(app_state_ptr) {
    M5.Display.setRotation(3); // Landscape - Main button the left
    M5.Display.setTextDatum(middle_center);
}

void ViewController::Draw() {
    M5.Display.clear();

    switch (app_state->stage) {
        case GPS_WAIT:
            displayGPSWaitTime();
            break;
        case WELCOME:
            displayWelcome();
            break;
        case VIEW_LAST_RUN:
            displayLastRun();
            break;
        case SETTINGS:
            displaySettings();
            break;
        case WAITING_FOR_STAGING:
            displayWaitingForStaging();
            break;
        case STAGING:
            displayStaging();
            break;
        case TIMING:
            displaySpeedometer();
            displayTiming();
            break;
    }

    displayBattery();
    if (app_state->stage != GPS_WAIT) {
        drawBackStage();
        displaysSatelliteCount();
    }
}

void ViewController::displaySettings() {
    M5.Display.setTextColor(WHITE);
    switch (app_state->settings_state) {
        case SELECTING_RUN_TYPE:
            M5.Display.setTextSize(5);
            M5.Display.setCursor(40, M5.Display.height() / 2);
            switch (app_state->run_mode) {
                case DRAG:
                    M5.Display.printf("DRAG");
                    break;
                case ROLL:
                    M5.Display.printf("ROLL");
                    break;
                default:
                    break;
            }
            break;
        case MODIFYING_ROLL_START:
            M5.Display.setCursor(20, M5.Display.height() / 2);
            M5.Display.setTextSize(3);
            M5.Display.printf("Start: %0.0f", app_state->settings_roll_params.x);
            break;
        case MODIFYING_ROLL_END:
            M5.Display.setCursor(20, M5.Display.height() / 2);
            M5.Display.setTextSize(3);
            M5.Display.printf("End: %0.0f", app_state->settings_roll_params.y);
            break;
    }
}

void ViewController::displayRollLastRun() {
    M5.Display.setCursor(12, 20);
    M5.Display.setTextSize(1.5);
    M5.Display.setTextColor(WHITE);
    M5.Display.printf("Last Run:\r\n");
    M5.Display.setCursor(12, 35);

    auto roll_runs = app_state->global_objects.run_controller->GetRollRuns();

    for (auto & run : roll_runs) {
        if (!run.is_completed) {continue;}
        if (GetSlope(run.starting_altitude, run.ending_altitude, run.starting_position, run.ending_position) < BAD_SLOPE_PERCENT) {
            M5.Display.setTextColor(ORANGE);
        } else {
            M5.Display.setTextColor(WHITE);
        }

        auto time = (run.time_at_completion - run.start_time) * MILLIS2SECS;
        M5.Display.printf("%s   %0.2f\r\n", run.name.c_str(), time);
        M5.Display.setCursor(12, M5.Display.getCursorY());
    }
}

void ViewController::displayDragLastRun() {
    M5.Display.setCursor(12, 20);
    M5.Display.setTextSize(1.5);
    M5.Display.setTextColor(WHITE);
    M5.Display.printf("Last Run:\r\n");
    M5.Display.setCursor(12, 35);


    auto drag_runs = app_state->global_objects.run_controller->GetDragRuns();
    for (auto & run : drag_runs) {
        std::visit([](auto& r) -> void {
            if (!r.is_completed) {return;}
            if (GetSlope(r.starting_altitude, r.ending_altitude, r.starting_position, r.ending_position) > BAD_SLOPE_PERCENT) {
                M5.Display.setTextColor(ORANGE);
            } else {
                M5.Display.setTextColor(WHITE);
            }
            auto time = (r.time_at_completion - r.start_time) * MILLIS2SECS;
            M5.Display.printf("%s   %0.2f\r\n", r.name.c_str(), time);
            M5.Display.setCursor(12, M5.Display.getCursorY());
        }, run);
    }
}

void ViewController::displayLastRun() {
    M5.Display.setCursor(12, 20);
    M5.Display.setTextSize(1.5);
    M5.Display.setTextColor(WHITE);
    M5.Display.printf("Last Run:\r\n");
    M5.Display.setCursor(12, 35);

    switch (app_state->run_mode) {
        case DRAG: {
            displayDragLastRun();
            break;
        }
        case ROLL: {
            displayRollLastRun();
            break;
        }
    }
}

void ViewController::displayBattery() {
    M5.Display.setCursor(200, 18);
    M5.Display.setTextSize(1.5);
    M5.Display.setTextColor(WHITE);

    const int16_t batteryVoltage = M5.Power.getBatteryVoltage();
    int percentage = map(batteryVoltage, 3700, 4200, 0, 100);
    percentage = constrain(percentage, 0, 100);
    M5.Display.printf("%d%%", percentage);
}

void ViewController::drawBackStage() {
    switch (app_state->stage) {
        case WELCOME:
            M5.Display.setColor(255, 0, 0);
            break;
        case VIEW_LAST_RUN:
            M5.Display.setColor(255, 0, 0);
            break;
        case STAGING:
            M5.Display.setColor(255, 255, 0);
            break;
        case WAITING_FOR_STAGING:
            M5.Display.setColor(255, 0, 0);
            break;
        case TIMING:
            M5.Display.setColor(0, 255, 0);
            break;
        default:
            M5.Display.setColor(0, 0, 0);
            break;
    }

    M5.Display.drawRect(5, 5, 230, 125);
}

void ViewController::displaySpeedometer() {
    auto current_speed = app_state->gps.current_speed;

    M5.Display.drawLine(173, 5, 173, 125, GREEN);

    M5.Display.setTextSize(2.5);
    M5.Display.setTextColor(WHITE);

    M5.Display.setCursor(183, 90);
    M5.Display.printf("%0.0f\r\n", current_speed);


    M5.Display.setTextSize(1.5);
    M5.Display.setCursor(185, M5.Display.getCursorY());
    M5.Display.printf("km/h");
}

void ViewController::displayGPSWaitTime() {
    M5.Display.clear();
    M5.Display.setCursor(40, M5.Display.height() / 2.5);
    M5.Display.setTextSize(2);
    M5.Display.setTextColor(WHITE);
    M5.Display.printf("Waiting for GPS\r\n");
    M5.Display.setCursor(40, M5.Display.getCursorY()+5);
    int waitingSeconds = millis() / 1000;
    M5.Display.printf("%ds\r\n", waitingSeconds);
}

void ViewController::displaysSatelliteCount() {
    M5.Display.setTextSize(1.5);
    M5.Display.setTextColor(WHITE);

    uint32_t sat_count = app_state->gps.satellite_count;

    if (app_state->stage == TIMING || app_state->stage == VIEW_LAST_RUN) {
        M5.Display.setCursor(203, 33);
        M5.Display.printf("Sat\r\n");
        M5.Display.setCursor(210, 48);
        M5.Display.printf("%d", sat_count);
    } else {
        M5.Display.setCursor(12, 18);
        M5.Display.printf("Sats: %d", sat_count);
    }
}

void ViewController::displayWelcome() {
    M5.Display.setCursor(40, M5.Display.height() / 2);
    M5.Display.setTextSize(4);
    M5.Display.setTextColor(WHITE);
    M5.Display.printf("WELCOME");
}

void ViewController::displayWaitingForStaging() {
    M5.Display.setTextSize(4);
    M5.Display.setCursor(40, M5.Display.height() / 2);
    M5.Display.setTextColor(RED);
    M5.Display.printf("WAITING");
}

void ViewController::displayStaging() {
    M5.Display.setTextSize(4);
    M5.Display.setCursor(65, M5.Display.height() / 2);
    M5.Display.setTextColor(YELLOW);
    M5.Display.printf("READY");
}

void ViewController::displayRollTiming() {
    M5.Display.setCursor(12, 20);
    M5.Display.setTextSize(1.5);
    M5.Display.setTextColor(WHITE);
    M5.Display.printf("Current Run:\r\n");
    M5.Display.setCursor(12, 35);

    auto roll_runs = app_state->global_objects.run_controller->GetRollRuns();

    for (auto & run : roll_runs) {
        double time;
        if (!run.is_completed) {
            time = (millis() - run.start_time) * MILLIS2SECS;
            M5.Display.setTextColor(WHITE);
        } else {
            time = (run.time_at_completion - run.start_time) * MILLIS2SECS;
            M5.Display.setTextColor(GREEN);
        }
        M5.Display.printf("%s   %0.2f\r\n", run.name.c_str(), time);
        M5.Display.setCursor(12, M5.Display.getCursorY());
    }
}

void ViewController::displayDragTiming() {
    M5.Display.setCursor(12, 20);
    M5.Display.setTextSize(1.5);
    M5.Display.setTextColor(WHITE);
    M5.Display.printf("Current Run:\r\n");
    M5.Display.setCursor(12, 35);


    bool there_is_a_uncompleted_run = false; // Dont display live time for runs following first uncompleted run (With Live Timing)
    auto drag_runs = app_state->global_objects.run_controller->GetDragRuns();
    for (auto & run : drag_runs) {
        std::visit([&there_is_a_uncompleted_run](auto& r) -> void {
            double time;
            if (!r.is_completed) {
                if (there_is_a_uncompleted_run == false) {
                    time = (millis() - r.start_time) * MILLIS2SECS;
                } else {
                    time = 0.0;
                }
                M5.Display.setTextColor(WHITE);
                there_is_a_uncompleted_run = true;
            } else {
                time = (r.time_at_completion - r.start_time) * MILLIS2SECS;
                M5.Display.setTextColor(GREEN);
            }

            M5.Display.printf("%s   %0.2f\r\n", r.name.c_str(), time);
            M5.Display.setCursor(12, M5.Display.getCursorY());
        }, run);
    }
}

void ViewController::displayTiming() {
    switch (app_state->run_mode) {
        case DRAG:
            displayDragTiming();
            break;
        case ROLL:
            displayRollTiming();
            break;
        default:
            break;
    }
}
