//
// Created by Hashm A on 2026-04-19.
//

#ifndef DRAGY_CPP_CONSTANTS_H
#define DRAGY_CPP_CONSTANTS_H

#include <HardwareSerial.h>

// SYSTEM
constexpr uint32_t FRAME_DELAY = 25;
constexpr int DEVICE_VOLUME = 50;

// GPS
constexpr uint32_t GPS_CONFIG = SERIAL_8N1;
constexpr uint32_t GPS_BAUD = 115200;
constexpr int GPS_RX_PIN = 33;
constexpr int GPS_TX_PIN = 32;

// RUN
constexpr float DRAG_LAUNCH_SPEED_THRESHOLD = 0.4f; // KMPH
constexpr float DRAG_STAGING_SPEED_THRESHOLD = 0.3f; // KMPH
constexpr float BAD_SLOPE_PERCENT = -0.01;

// CONVERSIONS
constexpr float SIXTY_MPH_IN_KMPH = 96.5606;
constexpr float QUARTER_MILE_IN_KM = 0.402336;
constexpr float EIGHT_MILE_IN_KM = QUARTER_MILE_IN_KM/2.0f;
constexpr float MI2KM = 1.60934;
constexpr double MILLIS2SECS = 0.001;
constexpr double M2KM = 0.001;
constexpr double KM2M = 1000;

#endif //DRAGY_CPP_CONSTANTS_H
