//
// Created by Hashm A on 2026-04-21.
//

#ifndef DRAGY_CPP_ROLLRUNMANAGER_H
#define DRAGY_CPP_ROLLRUNMANAGER_H

#include <vector>

#include "RollRun.h"

#include "state.h"

class RollRunManager : public ManagerData {
    RollTarget target_run{};

public:
    RollRunManager() = default;
    RollRunManager(const float starting_speed, const float ending_speed) : target_run(starting_speed, ending_speed) {}

    bool DoesLastRunExist() override {
        return target_run.is_completed;
    }

    void ResetRuns() {
        target_run.ResetRun();
    }

    std::vector<RollTarget> GetRuns() {
        return std::vector<RollTarget>{target_run};
    }

    void LaunchRuns(AppState * app_state) {
        target_run.Launch(app_state);

        LaunchSelf(app_state);
    }

    void CheckForLaunch(AppState * app_state) {
        if (app_state->gps.current_speed >= target_run.start_speed) {
            LaunchRuns(app_state);
            app_state->SetStage(TIMING);
        }
    }

    void EndAllRunsPrematurely(AppState * app_state) {
        target_run.EndRunTargetPremature();

        EndSelf(app_state);

        // if (DoesLastRunExist()) {
            app_state->SetStage(VIEW_LAST_RUN);
        // } else {
            // app_state->SetStage(WELCOME);
        // }
    }

    void UpdateRuns(AppState * app_state) {
        target_run.UpdateRunData(app_state);

        UpdateSelf(app_state);
    }

    // Update Runs
};

#endif //DRAGY_CPP_ROLLRUNMANAGER_H
