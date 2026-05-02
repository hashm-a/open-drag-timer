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
    double starting_altitude{}; // in meters

    Vector2 ending_position{};
    double ending_altitude{}; // in meters

    std::vector<double> hdop_readings{};
    std::vector<uint32_t> satellite_readings{};

    // Calculated Only Once
    double total_run_distance_meter{};
    double total_run_slope{};

    int avg_num_of_satellites{};
    double avg_hdop_reading{};

    bool calculations_are_completed{};

protected:
    void LaunchSelf(const AppState & app_state) {
        ResetSelf();

        starting_position = app_state.gps.location;
        starting_altitude = app_state.gps.altitude;
    }
    
    void UpdateSelf(const AppState & app_state) {
        hdop_readings.push_back(app_state.gps.current_HDOP);
        satellite_readings.push_back(app_state.gps.satellite_count);
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

        if (total_run_distance_meter == 0) {
            total_run_slope = 0.0;
        } else {
            total_run_slope = GetSlope(starting_altitude, ending_altitude, starting_position, ending_position);
        }

        if (hdop_readings.empty()) {
            avg_hdop_reading = 80.8;
        } else {
            avg_hdop_reading = std::accumulate(hdop_readings.begin(), hdop_readings.end(), 0.0) / std::size(hdop_readings);
        }

        if (satellite_readings.empty()) {
            avg_num_of_satellites = 0;
        } else {
            avg_num_of_satellites = static_cast<int>(std::accumulate(satellite_readings.begin(), satellite_readings.end(), 0LL) / std::size(satellite_readings));
        }
    }

    void ResetSelf() {
        starting_position = {};
        starting_altitude = {};

        ending_position = {};
        ending_altitude = {};

        total_run_distance_meter = {};
        total_run_slope = {};
    }

public:
    virtual ~ManagerData() = default;
    // IMP by real controller
    virtual bool DoesLastRunExist() = 0;

    bool IsRunValid(const AppState & app_state) {
        if (!calculations_are_completed) {
            EndSelf(app_state);
        }

        if (!IsSlopeValid(total_run_slope)) {
            return false;
        }

        if (avg_num_of_satellites < MIN_GOOD_SATELLITE_COUNT) {
            return false;
        }

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
        return total_run_slope * 100.0;
    }

    double GetAverageHDOP(const AppState & app_state) {
        if (!calculations_are_completed) {
            EndSelf(app_state);
        }
        return avg_hdop_reading;
    }
};

#endif //DRAGY_CPP_MANAGERDATA_H
