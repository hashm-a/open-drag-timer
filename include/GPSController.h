//
// Created by Hashm A on 2026-04-19.
//

#ifndef DRAGY_CPP_GPSController_H
#define DRAGY_CPP_GPSController_H

#include <GPSInterface.h>

#include "state.h"

class GPSController {
    AppState & app_state;
    GPSInterface gps_interface;

public:
    GPSController(AppState & tracked_app_state, HardwareSerial& serialPort, long baudRate, uint32_t config, int rxPin, int txPin);

    void Update();

private:
    void updateHDOP();

    void updateSatellites();

    void updateSpeed();

    void updateLocation();

    void updateAltitude();
};

#endif //DRAGY_CPP_GPSController_H
