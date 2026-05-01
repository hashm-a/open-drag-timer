//
// Created by Hashm A on 2026-04-21.
//

#ifndef DRAGY_CPP_DRAGRUNMANAGER_H
#define DRAGY_CPP_DRAGRUNMANAGER_H

#include "DragRun.h"
#include "ManagerData.h"

#include "state.h"
#include "constants.h"
#include "DragRunPresets.h"

using DragRunVariants = std::variant<DragSpeedTarget, DragDistanceTarget>;

class DragRunManager : public ManagerData {
    std::array<DragRunVariants, 5> run_targets;

public:
    DragRunManager() : run_targets(DEFAULT_PRESET) {}

    bool DoesLastRunExist() override {
        bool a_run_exists = false;
        for (auto & t: run_targets) {
            std::visit([&a_run_exists](const auto& run) -> void {
                if (run.is_completed) {
                    a_run_exists = true;
                }
            }, t);
        }

        return a_run_exists;
    }

    void ResetRuns() {
        for (auto & target: run_targets) {
            std::visit([](auto &t) {
                t.ResetRun();
            }, target);
        }
    }

    std::vector<DragRunVariants> GetRuns() {
        return std::vector(run_targets.begin(),run_targets.end());
    }

    void LaunchRuns(AppState & app_state) {
        for (auto & t: run_targets) {
            std::visit([&app_state](auto& run) -> void {
                run.Launch(app_state);
            }, t);
        }

        LaunchSelf(app_state);
    }

    void CheckForLaunch(AppState & app_state) {
        if (app_state.gps.current_speed >= DRAG_LAUNCH_SPEED_THRESHOLD) {
            LaunchRuns(app_state);
            app_state.SetStage(TIMING);
        }
    }

    void EndAllRunsPrematurely(AppState & app_state) {
        for (auto & t: run_targets) {
            std::visit([](auto& run) -> void {
                run.EndRunTargetPremature();
            }, t);
        }

        EndSelf(app_state);

        // if (DoesLastRunExist()) {
            app_state.SetStage(VIEW_LAST_RUN);
        // } else {
            // app_state.SetStage(WELCOME);
        // }
    }

    void UpdateRuns(AppState & app_state) {
        for (auto & t: run_targets) {
            std::visit([&app_state](auto& run) -> void {
                run.UpdateRunData(app_state);
            }, t);
        }

        UpdateSelf(app_state);
    }
};

#endif //DRAGY_CPP_DRAGRUNMANAGER_H
