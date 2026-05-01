#include <M5Unified.h>
#include <Arduino.h>

#include "MasterController.h"

#include "state.h"
#include "constants.h"

AppState * app_state = nullptr;
MasterController *  controller = nullptr;

void setup() {
    M5.begin(m5::M5Unified::config());

    app_state = new AppState();
    controller = new MasterController(app_state);
}

void loop() {
    controller->Update();
    delay(FRAME_DELAY);
}