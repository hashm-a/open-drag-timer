//
// Created by Hashm A on 2026-04-19.
//

// #include <M5StickCPlus2.h>
#include <M5Unified.h>

#include "AudioController.h"

#include "constants.h"

void AudioController::PlayBeep() {
    M5.Speaker.setVolume(DEVICE_VOLUME);
    M5.Speaker.tone(5000, 50);
}
