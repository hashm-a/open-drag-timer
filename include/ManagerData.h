//
// Created by Hashm A on 2026-04-27.
//

#ifndef DRAGY_CPP_MANAGERDATA_H
#define DRAGY_CPP_MANAGERDATA_H

#include <numeric>

#include "gpsmath.h"
#include "constants.h"
#include "state.h"
#include "types.h"

class ManagerData {
private:
    Vector2 starting_position{};
    int starting_altitude{}; // in meters

    Vector2 ending_position{};
    int ending_altitude{}; // in meters

    std::vector<float> hdop_readings{};
    std::vector<int> satellite_readings{};

    // Calculated Only Once
    double total_run_distance_meter{};
    double total_run_slope_percent{};

    float avg_num_of_satellites{};
    float avg_hdop_reading{};

    bool calculations_are_completed{};

protected:
    void LaunchSelf(const AppState & app_state) {
        ResetSelf();

        starting_position = app_state.gps.location;
        starting_altitude = app_state.gps.altitude;
    }
    
    void UpdateSelf(const AppState & app_state) {
        hdop_readings.push_back(app_state.gps.current_HDOP);
    }

    void EndSelf(const AppState & app_state) {
        if (!DoesLastRunExist()) {
            return;
        }

        ending_position = app_state.gps.location;
        ending_altitude = app_state.gps.altitude;
        calculations_are_completed = true;

        // Calculations
        total_run_distance_meter = GetDistanceBetweenInM(starting_position, ending_position);
        total_run_slope_percent = ((ending_altitude - starting_altitude) / total_run_distance_meter) * 100; // %

        avg_hdop_reading = std::accumulate(hdop_readings.begin(), hdop_readings.end(), 0LL) / std::size(hdop_readings);
        avg_num_of_satellites = std::accumulate(satellite_readings.begin(), satellite_readings.end(), 0LL) / std::size(satellite_readings);
    }

    void ResetSelf() {
        starting_position = {};
        starting_altitude = {};

        ending_position = {};
        ending_altitude = {};

        total_run_distance_meter = {};
        total_run_slope_percent = {};
    }

public:
    virtual ~ManagerData() = default;
    // IMP by real controller
    virtual bool DoesLastRunExist() = 0;

    bool IsRunValid(const AppState & app_state) {
        if (!calculations_are_completed) {
            EndSelf(app_state);
        }

        if (total_run_slope_percent < MAX_DOWNWARD_SLOPE_PERCENT) {
            return false;
        }

        // Off for debug
        // if (avg_num_of_satellites <= MIN_GOOD_SATELLITE_COUNT) {
        //     return false;
        // }

        if (avg_hdop_reading > VALID_HDOP_MAX) {
            return false;
        }

        return true;
    }

    double GetTotalRunDistance(const AppState & app_state) {
        if (!calculations_are_completed) {
            EndSelf(app_state);
        }
        return total_run_distance_meter;
    }

    double GetRunSlopePercent(const AppState & app_state) {
        if (!calculations_are_completed) {
            EndSelf(app_state);
        }
        return total_run_slope_percent;
    }
};

#endif //DRAGY_CPP_MANAGERDATA_H
