//
// Created by Hashm A on 2026-04-19.
//

#ifndef DRAGY_CPP_CONSTANTS_H
#define DRAGY_CPP_CONSTANTS_H

#include <HardwareSerial.h>

// SYSTEM
constexpr unsigned int FRAME_DELAY = 33; // ms (approx 30fps or 3x positioning refresh rate)
constexpr unsigned int DEVICE_VOLUME = 50;

// GPS
constexpr uint32_t GPS_CONFIG = SERIAL_8N1;
constexpr uint32_t GPS_BAUD = 115200;
constexpr unsigned int GPS_RX_PIN = 33;
constexpr unsigned int GPS_TX_PIN = 32;

// RUN
constexpr float DRAG_LAUNCH_SPEED_THRESHOLD = 0.4f; // KMPH
constexpr float DRAG_STAGING_SPEED_THRESHOLD = 0.3f; // KMPH

constexpr float MAX_DOWNWARD_SLOPE = -0.01f;

constexpr float VALID_HDOP_MAX = 2.5f;
constexpr unsigned int MIN_GOOD_SATELLITE_COUNT = 6;

// DEFAULTS
constexpr unsigned int DEFAULT_ROLL_START = 50;
constexpr unsigned int DEFAULT_ROLL_END = 100;

// CONVERSIONS
constexpr double M2KM = 0.001;
constexpr double KM2M = 1000;
constexpr float MI2KM = 1.60934;
constexpr double MILLIS2SECS = 0.001;

// CONVERTED VALUES
constexpr float SIXTY_MPH_IN_KMPH = 60 * MI2KM;
constexpr float QUARTER_MILE_IN_KM = 0.25f * MI2KM;
constexpr float EIGHT_MILE_IN_KM = QUARTER_MILE_IN_KM/2.0f;

#endif //DRAGY_CPP_CONSTANTS_H
