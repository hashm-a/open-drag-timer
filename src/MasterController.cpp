//
// Created by Hashm A on 2026-04-19.
//

#include "MasterController.h"

#include <constants.h>
#include <ViewController.h>
#include <InputController.h>
#include <GPSController.h>


MasterController::MasterController(AppState * tracked_app_state) : gps_controller(tracked_app_state, Serial1, GPS_BAUD, GPS_CONFIG, GPS_RX_PIN, GPS_TX_PIN),
                                       input_controller(tracked_app_state),
                                       view_controller(tracked_app_state),
                                       run_controller(tracked_app_state) {
    app_state = tracked_app_state;
    tracked_app_state->SetRunController(&run_controller);
}

void MasterController::Update() {
    gps_controller.Update();
    input_controller.UpdateInput();
    view_controller.Draw();
    run_controller.Update();

    if (app_state->gps.IsReady() && app_state->stage == GPS_WAIT) {app_state->SetStage(WELCOME);}
}
