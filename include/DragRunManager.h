//
// Created by Hashm A on 2026-04-21.
//

#ifndef DRAGY_CPP_DRAGRUNMANAGER_H
#define DRAGY_CPP_DRAGRUNMANAGER_H

#include "DragRun.h"
#include "state.h"
#include "constants.h"
#include "DragRunPresets.h"

using DragRunVariants = std::variant<DragSpeedTarget, DragDistanceTarget>;

class DragRunManager {
    std::array<DragRunVariants, 5> run_targets;

public:
    DragRunManager() : run_targets(DEFAULT_PRESET) {}

    // void ResetRuns() override {
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

    void CheckForLaunch(AppState * app_state) {
        if (app_state->gps.current_speed >= DRAG_LAUNCH_SPEED_THRESHOLD) {
            for (auto & t: run_targets) {
                std::visit([&app_state](auto& run) -> void {
                    run.Launch(app_state);
                }, t);
            }

            app_state->SetStage(TIMING);
        }
    }

    void EndAllRunsPrematurely(AppState * app_state) {
        bool a_run_exists = false;
        for (auto & t: run_targets) {
            std::visit([&a_run_exists](auto& run) -> void {
                run.EndRunTargetPremature();
                if (run.is_completed) {
                    a_run_exists = true;
                }
            }, t);
        }
        app_state->last_run_exists = a_run_exists;
        app_state->SetStage(VIEW_LAST_RUN);
    }

    void UpdateRuns(AppState * app_state) {
        for (auto & t: run_targets) {
            std::visit([&app_state](auto& run) -> void {
                run.UpdateRunData(app_state);
            }, t);
        }
    }
};

#endif //DRAGY_CPP_DRAGRUNMANAGER_H
