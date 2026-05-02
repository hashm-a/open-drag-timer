#include <M5Unified.h>
#include <Arduino.h>

#include "MasterController.h"

#include "state.h"

AppState app_state{};
MasterController *  controller = nullptr;

void setup() {
    M5.begin(m5::M5Unified::config());

    controller = new MasterController(app_state);
}

void loop() {
    controller->Update();
}