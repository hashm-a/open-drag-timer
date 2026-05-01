//
// Created by Hashm A on 2026-04-20.
//

#include <RunController.h>
#include <state.h>

RunController::RunController(AppState * app_state_reference) : app_state(app_state_reference) {}

void RunController::Update() {
    switch (app_state->stage) {
        case WAITING_FOR_STAGING:
            WaitForStage();
            break;
        case STAGING:
            CheckIfLaunched();
            break;
        case TIMING:
            UpdateRuns();
            break;
        default:
            break;
    }

    app_state->last_run_exists = DoesLastRunExist();
}

bool RunController::DoesLastRunExist() {
    switch (app_state->run_mode) {
        case DRAG:
            return drag_run_manager.DoesLastRunExist();
        case ROLL:
            return roll_run_manager.DoesLastRunExist();
        default:
            return false;
    }

}

bool RunController::IsLastRunValid() {
    switch (app_state->run_mode) {
        case DRAG:
            return drag_run_manager.IsRunValid(app_state);
        case ROLL:
            return roll_run_manager.IsRunValid(app_state);
        default:
            return false;
    }
}

double RunController::GetTotalRunDistance() {
    switch (app_state->run_mode) {
        case DRAG:
            return drag_run_manager.GetTotalRunDistance(app_state);
        case ROLL:
            return roll_run_manager.GetTotalRunDistance(app_state);
        default:
            return 0.0;
    }
}

double RunController::GetRunSlopePercent() {
    switch (app_state->run_mode) {
        case DRAG:
            return drag_run_manager.GetRunSlopePercent(app_state);
        case ROLL:
            return roll_run_manager.GetRunSlopePercent(app_state);
        default:
            return 0.0;
    }
}

void RunController::UpdateRuns() {
    switch (app_state->run_mode) {
        case DRAG:
            drag_run_manager.UpdateRuns(app_state);
            break;
        case ROLL:
            roll_run_manager.UpdateRuns(app_state);
            break;
        default:
            break;
    }
}

void RunController::WaitForStage() {
    switch (app_state->run_mode) {
        case DRAG: {
            if (app_state->gps.current_speed <= DRAG_STAGING_SPEED_THRESHOLD) {
                app_state->SetStage(STAGING);
                break;
            }
            break;
        }
        case ROLL: {
            double min_roll_speed = infinity();
            auto roll_data = GetRollRuns();
            for (const auto& roll : roll_data) {
                if (roll.start_speed < min_roll_speed) {min_roll_speed = roll.start_speed;}
            }

            if (app_state->gps.current_speed < min_roll_speed) {
                app_state->SetStage(STAGING);
                break;
            }
            break;
        }
        default:
            break;
    }
}

void RunController::CheckIfLaunched() {
    switch (app_state->run_mode) {
        case DRAG:
            drag_run_manager.CheckForLaunch(app_state);
            break;
        case ROLL:
            roll_run_manager.CheckForLaunch(app_state);
            break;
        default:
            break;
    }
}

// void RunController::ResetAllRuns() {
//     drag_run_manager.ResetRuns();
//     roll_run_manager.ResetRuns();
// }

void RunController::EndCurrentRunPrematurely() {
    switch (app_state->run_mode) {
        case DRAG:
            drag_run_manager.EndAllRunsPrematurely(app_state);
            break;
        case ROLL:
            roll_run_manager.EndAllRunsPrematurely(app_state);
            break;
        default:
            break;
    }
}

// G/S
void RunController::SetRoll(const float start_speed, const float end_speed) {
    roll_run_manager = RollRunManager(start_speed, end_speed);
}

std::vector<DragRunVariants> RunController::GetDragRuns() {
    return drag_run_manager.GetRuns();
}

std::vector<RollTarget> RunController::GetRollRuns() {
    return roll_run_manager.GetRuns();
}
