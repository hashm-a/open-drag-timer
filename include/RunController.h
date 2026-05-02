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
    AppState & app_state;
    DragRunManager drag_run_manager;
    RollRunManager roll_run_manager;

public:
    RunController(AppState & tracked_app_state);

    bool DoesLastRunExist();

    bool IsLastRunValid();

    double GetTotalRunDistance();

    double GetAverageHDOP();

    double GetRunSlopePercent();

    void Update();

    void UpdateRuns();

    void EndCurrentRunPrematurely();

    void SetRoll(float start_speed, float end_speed);

    std::vector<DragRunVariants> GetDragRuns();

    std::vector<RollTarget> GetRollRuns();

    void WaitForStage();

    void CheckIfLaunched();
};

#endif //DRAGY_CPP_RUNCONTROLLER_H
