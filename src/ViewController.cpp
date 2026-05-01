//
// Created by Hashm A on 2026-04-19.
//
#include "state.h"

#include "ViewController.h"
#include "RunController.h"

#include <M5Unified.h>

ViewController::ViewController(AppState * app_state_ptr) : app_state(app_state_ptr) {
    display_buffer.createSprite(M5.Lcd.width(), M5.Lcd.height());
    display_buffer.setRotation(3); // Landscape - Main button the left
    display_buffer.setTextDatum(middle_center);
}

void ViewController::Draw() {
    display_buffer.clear();

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

    display_buffer.pushSprite(&M5.Lcd, 0,0);
}

void ViewController::displaySettings() {
    display_buffer.setTextColor(WHITE);
    switch (app_state->settings_state) {

        case SELECTING_RUN_TYPE: {
            display_buffer.setTextSize(5);
            display_buffer.setCursor(60, display_buffer.height() / 2);
            switch (app_state->run_mode) {
                case DRAG:
                    display_buffer.printf("DRAG");
                    break;
                case ROLL:
                    display_buffer.printf("ROLL");
                    break;
                default:
                    break;
            }
            break;
        }

        case MODIFYING_ROLL_START: {
            display_buffer.setCursor(15, display_buffer.height() / 2);
            display_buffer.setTextSize(3);
            display_buffer.printf("Start: ");
            int cursor_pos_x_start = display_buffer.getCursorX();
            display_buffer.printf("%0.0f\n", app_state->settings_roll_params.x);
            display_buffer.setCursor(cursor_pos_x_start, display_buffer.getCursorY() + 5);
            display_buffer.printf("km/h");
            break;
        }

        case MODIFYING_ROLL_END: {
            display_buffer.setCursor(15, display_buffer.height() / 2);
            display_buffer.setTextSize(3);
            display_buffer.printf("End:   ");
            int cursor_pos_x_end = display_buffer.getCursorX();
            display_buffer.printf("%0.0f\n", app_state->settings_roll_params.y);
            display_buffer.setCursor(cursor_pos_x_end, display_buffer.getCursorY() + 5);
            display_buffer.printf("km/h");
            break;
        }

    }
}

void ViewController::displayBattery() {
    display_buffer.setCursor(198, 18);
    display_buffer.setTextSize(1.5);
    display_buffer.setTextColor(WHITE);

    const int16_t batteryVoltage = M5.Power.getBatteryVoltage();
    int percentage = map(batteryVoltage, 3700, 4200, 0, 100);
    percentage = constrain(percentage, 0, 100);
    display_buffer.printf("%d%%", percentage);
}

void ViewController::drawBackStage() {
    switch (app_state->stage) {
        case WELCOME:
            display_buffer.setColor(255, 0, 0);
            break;
        case VIEW_LAST_RUN:
            display_buffer.setColor(255, 0, 0);
            break;
        case STAGING:
            display_buffer.setColor(255, 255, 0);
            break;
        case WAITING_FOR_STAGING:
            display_buffer.setColor(255, 0, 0);
            break;
        case TIMING:
            display_buffer.setColor(0, 255, 0);
            break;
        default:
            display_buffer.setColor(0, 0, 0);
            break;
    }

    display_buffer.drawRect(5, 5, 230, 125);
}

void ViewController::displaySpeedometer() {
    const double current_speed = app_state->gps.current_speed;

    display_buffer.drawLine(173, 5, 173, 125, GREEN);

    display_buffer.setTextSize(2.5);
    display_buffer.setTextColor(WHITE);

    display_buffer.setCursor(183, 90);
    display_buffer.printf("%0.0f\r\n", current_speed);


    display_buffer.setTextSize(1.5);
    display_buffer.setCursor(185, display_buffer.getCursorY());
    display_buffer.printf("km/h");
}

void ViewController::displayGPSWaitTime() {
    display_buffer.clear();
    display_buffer.setCursor(40, static_cast<int>(display_buffer.height() / 2.5));
    display_buffer.setTextSize(2);
    display_buffer.setTextColor(WHITE);
    display_buffer.printf("Waiting for GPS\r\n");
    display_buffer.setCursor(40, display_buffer.getCursorY()+5);
    const int waitingSeconds = static_cast<int>(millis() / 1000);
    display_buffer.printf("%ds\r\n", waitingSeconds);
}

void ViewController::displaysSatelliteCount() {
    display_buffer.setTextSize(1.5);
    display_buffer.setTextColor(WHITE);

    const uint32_t satellite_count = app_state->gps.satellite_count;
    const float current_HDOP = app_state->gps.current_HDOP;

    const bool hdop_and_sat = (current_HDOP <= VALID_HDOP_MAX) && (satellite_count >= MIN_GOOD_SATELLITE_COUNT);

    const int satellite_validity_color = hdop_and_sat ? WHITE : ORANGE;

    if (app_state->stage == TIMING || app_state->stage == VIEW_LAST_RUN) {
        display_buffer.setCursor(203, 33);
        display_buffer.printf("Sat\r\n");
        display_buffer.setCursor(210, 48);
        display_buffer.setTextColor(satellite_validity_color);
        display_buffer.printf("%d", satellite_count);
    } else {
        display_buffer.setCursor(12, 18);
        display_buffer.printf("Sats: ");
        display_buffer.setTextColor(satellite_validity_color);
        display_buffer.printf("%d", satellite_count);
    }
}

void ViewController::displayWelcome() {
    display_buffer.setCursor(40, display_buffer.height() / 2);
    display_buffer.setTextSize(4);
    display_buffer.setTextColor(WHITE);
    display_buffer.printf("WELCOME");
}

void ViewController::displayWaitingForStaging() {
    display_buffer.setTextSize(4);
    display_buffer.setCursor(40, display_buffer.height() / 2);
    display_buffer.setTextColor(RED);
    display_buffer.printf("WAITING");
}

void ViewController::displayStaging() {
    display_buffer.setTextSize(4);
    display_buffer.setCursor(65, display_buffer.height() / 2);
    display_buffer.setTextColor(YELLOW);
    display_buffer.printf("READY");
}

// Current Run
void ViewController::displayTiming() {
    display_buffer.setCursor(12, 20);
    display_buffer.setTextSize(1.5);
    display_buffer.setTextColor(WHITE);
    display_buffer.printf("Current Run:\r\n");
    display_buffer.setCursor(12, 35);

    switch (app_state->run_mode) {
        case DRAG:
            displayCurrentDragTiming();
            break;
        case ROLL:
            displayCurrentRollTiming();
            break;
        default:
            break;
    }
}

void ViewController::displayCurrentRollTiming() {
    display_buffer.setTextSize(2.5); // Roll size buff as less roll runs than drags
    const auto roll_runs = app_state->global_objects.run_controller->GetRollRuns();

    for (auto & run : roll_runs) {
        double time;
        if (!run.is_completed) {
            time = (millis() - run.start_time) * MILLIS2SECS;
            display_buffer.setTextColor(WHITE);
        } else {
            time = (run.time_at_completion - run.start_time) * MILLIS2SECS;
            display_buffer.setTextColor(GREEN);
        }
        display_buffer.printf("%s:   %0.2fs\r\n", run.name.c_str(), time);
        display_buffer.setCursor(12, display_buffer.getCursorY());
    }
}

void ViewController::displayCurrentDragTiming() {
    bool there_is_a_uncompleted_run = false; // Dont display live time for runs following first uncompleted run (With Live Timing)

    const auto drag_runs = app_state->global_objects.run_controller->GetDragRuns();

    for (auto & run : drag_runs) {
        std::visit([&there_is_a_uncompleted_run, this](auto& r) -> void {
            double time;
            if (!r.is_completed) {
                if (there_is_a_uncompleted_run == false) {
                    time = (millis() - r.start_time) * MILLIS2SECS;
                } else {
                    time = 0.0;
                }
                display_buffer.setTextColor(WHITE);
                there_is_a_uncompleted_run = true;
            } else {
                time = (r.time_at_completion - r.start_time) * MILLIS2SECS;
                display_buffer.setTextColor(GREEN);
            }

            display_buffer.printf("%s:   %0.2fs\r\n", r.name.c_str(), time);
            display_buffer.setCursor(12, display_buffer.getCursorY());
        }, run);
    }
}

// Last Runs
void ViewController::displayLastRun() {
    display_buffer.setCursor(12, 20);
    display_buffer.setTextSize(1.5);
    display_buffer.setTextColor(WHITE);
    display_buffer.printf("Last Run: ");

    const int status_circle_color = app_state->global_objects.run_controller->IsLastRunValid() ? GREEN : RED;
    display_buffer.drawCircle(display_buffer.getCursorX() + 10, display_buffer.getCursorY(), 10, status_circle_color);

    switch (app_state->run_mode) {
        case DRAG: {
            displayLastDragRun();
            break;
        }
        case ROLL: {
            displayLastRollRun();
            break;
        }
        default:
            break;
    }

    // Display Total Distance traveled & slope via completion in super run class
    display_buffer.setCursor(12, 120);
    display_buffer.setTextColor(WHITE);
    display_buffer.setTextSize(1.5);

    const double total_distance_travelled = app_state->global_objects.run_controller->GetTotalRunDistance();
    display_buffer.printf("DIST: %0.1fm, ", total_distance_travelled);

    const double total_slope_percent = app_state->global_objects.run_controller->GetRunSlopePercent();
    const int slope_color = (total_slope_percent > MAX_DOWNWARD_SLOPE_PERCENT) ? GREEN : RED;
    display_buffer.setTextColor(slope_color);
    display_buffer.printf("SLP: %0.1f%%\r\n", total_slope_percent);
}


void ViewController::displayLastRollRun() {
    display_buffer.setTextSize(1.75);
    display_buffer.setCursor(12, 35);

    const auto roll_runs = app_state->global_objects.run_controller->GetRollRuns();

    for (auto & run : roll_runs) {
        if (!run.is_completed) {continue;}
        if (GetSlope(run.starting_altitude, run.ending_altitude, run.starting_position, run.ending_position) < MAX_DOWNWARD_SLOPE_PERCENT) {
            display_buffer.setTextColor(ORANGE);
        } else {
            display_buffer.setTextColor(WHITE);
        }

        auto time = (run.time_at_completion - run.start_time) * MILLIS2SECS;
        display_buffer.printf("%s:   %0.2fs\r\n", run.name.c_str(), time);
        display_buffer.setCursor(12, display_buffer.getCursorY());
    }
}

void ViewController::displayLastDragRun() {
    display_buffer.setTextSize(1.75);
    display_buffer.setCursor(12, 35);

    const auto drag_runs = app_state->global_objects.run_controller->GetDragRuns();

    for (auto & run : drag_runs) {
        std::visit([this](auto& r) -> void {
            if (!r.is_completed) {return;}
            if (GetSlope(r.starting_altitude, r.ending_altitude, r.starting_position, r.ending_position) > MAX_DOWNWARD_SLOPE_PERCENT) {
                display_buffer.setTextColor(ORANGE);
            } else {
                display_buffer.setTextColor(WHITE);
            }

            auto time = (r.time_at_completion - r.start_time) * MILLIS2SECS;
            display_buffer.printf("%s:   %0.2fs\r\n", r.name.c_str(), time);
            display_buffer.setCursor(12, display_buffer.getCursorY()+5);
        }, run);
    }
}