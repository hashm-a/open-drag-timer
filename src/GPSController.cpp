//
// Created by Hashm A on 2026-04-19.
//

#include "GPSController.h"

#include <GPSInterface.h>
#include <state.h>


GPSController::GPSController(AppState * app_state_ptr,
                             HardwareSerial &serialPort,
                             const long baudRate,
                             const uint32_t config,
                             const int rxPin,
                             const int txPin)
                             : app_state(app_state_ptr),
                               gps_interface(serialPort, baudRate, config, rxPin, txPin)
{
    gps_interface.begin();
    delay(500);
    gps_interface.setSystemBootMode(BOOT_COLD_START);
    delay(500);
    gps_interface.setSatelliteMode(SATELLITE_MODE_GPSGLONASSGALILEO);
    delay(500);
    gps_interface.increaseRefreshRate();
    delay(500);
    gps_interface.reduceLatency();
    delay(500);
    gps_interface.disableFilters();
}

void GPSController::Update() {
    gps_interface.updateGPS();
    updateSatellites();
    updateSpeed();
    updateLocation();
    updateAltitude();
    updateHDOP();
}

void GPSController::updateHDOP() {
    if (gps_interface.hdop.isValid()) {
        app_state->gps.current_HDOP = gps_interface.hdop.hdop();
    }
}

void GPSController::updateSatellites() {
    if (gps_interface.satellites.isValid()) {
        app_state->gps.satellite_count = gps_interface.satellites.value();
    }
}

void GPSController::updateSpeed() {
    if (gps_interface.speed.isValid()) {
        app_state->gps.current_speed = gps_interface.speed.kmph();
    }
}

void GPSController::updateLocation() {
    if (gps_interface.location.isValid()) {
        app_state->gps.location = {gps_interface.location.lat(), gps_interface.location.lng()};
    }
}

void GPSController::updateAltitude() {
    if (gps_interface.altitude.isValid()) {
        app_state->gps.altitude = gps_interface.altitude.value();
    }
}

