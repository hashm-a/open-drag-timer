//
// Created by Hashm A on 2026-04-20.
//

#ifndef DRAGY_CPP_RUNCONTROLLER_H
#define DRAGY_CPP_RUNCONTROLLER_H

#include <variant>
#include <vector>

#include "DragRunManager.h"
#include "RollRunManager.h"
#include "state.h"

class RunController {
    DragRunManager drag_run_manager;
    RollRunManager roll_run_manager;
    AppState * app_state;

public:
    RunController(AppState * app_state_reference);

    bool DoesLastRunExist();

    bool IsLastRunValid();

    double GetTotalRunDistance();

    double GetRunSlopePercent();

    void Update();

    void UpdateRuns();

    // void ResetAllRuns();

    void EndCurrentRunPrematurely();

    void SetRoll(float start_speed, float end_speed);

    std::vector<DragRunVariants> GetDragRuns();

    std::vector<RollTarget> GetRollRuns();

    void WaitForStage();

    void CheckIfLaunched();
};

#endif //DRAGY_CPP_RUNCONTROLLER_H
