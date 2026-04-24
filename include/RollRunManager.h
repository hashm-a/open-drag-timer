//
// Created by Hashm A on 2026-04-21.
//

#ifndef DRAGY_CPP_ROLLRUNMANAGER_H
#define DRAGY_CPP_ROLLRUNMANAGER_H

#include "RollRun.h"
#include "state.h"
#include <vector>

// class RollRunManager : public RunManager {
class RollRunManager {
    RollTarget target_run{};

public:
    RollRunManager() = default;
    RollRunManager(const float starting_speed, const float ending_speed) : target_run(starting_speed, ending_speed) {}

    // void ResetRuns() override {
    void ResetRuns() {
        target_run.ResetRun();
    }

     // std::vector<RunVariants> GetRuns() override {
    std::vector<RollTarget> GetRuns() {
        return std::vector<RollTarget>{target_run};
    }

    // void CheckForLaunch(AppState & app_state) override {
    void CheckForLaunch(AppState * app_state) {
        if (app_state->gps.current_speed >= target_run.start_speed) {
            target_run.Launch(app_state);
            app_state->SetStage(TIMING);
        }
    }

    void EndAllRunsPrematurely(AppState * app_state) {
        target_run.EndRunTargetPremature();
        app_state->last_run_exists = target_run.is_completed;

        app_state->SetStage(VIEW_LAST_RUN);
    }

    void UpdateRuns(AppState * app_state) {
        target_run.UpdateRunData(app_state);
    }

    // Update Runs
};

#endif //DRAGY_CPP_ROLLRUNMANAGER_H
