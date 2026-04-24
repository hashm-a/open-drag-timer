//
// Created by Hashm A on 2026-04-21.
//

#ifndef DRAGY_CPP_DRAGRUNPRESETS_H
#define DRAGY_CPP_DRAGRUNPRESETS_H
#include <variant>

#include "DragRun.h"

using DragRunVariants = std::variant<DragSpeedTarget, DragDistanceTarget>;
using DragRunPreset = std::array<DragRunVariants, 5>;

inline DragRunPreset DEFAULT_PRESET = {
    DragSpeedTarget{"0-50", 50},
    DragSpeedTarget{"0-60m", SIXTY_MPH_IN_KMPH},
    DragSpeedTarget{"0-100", 100},
    DragDistanceTarget{"1/8 mi", EIGHT_MILE_IN_KM},
    DragDistanceTarget{"1/4 mi", QUARTER_MILE_IN_KM}
};

inline DragRunPreset MPH_PRESET = {
    DragSpeedTarget{"0-30m", 30*MI2KM},
    DragSpeedTarget{"0-60m", SIXTY_MPH_IN_KMPH},
    DragDistanceTarget{"1/8 mi", EIGHT_MILE_IN_KM},
    DragDistanceTarget{"1/4 mi", QUARTER_MILE_IN_KM},
    DragDistanceTarget{"1/2 mi", QUARTER_MILE_IN_KM*2}
};

inline std::array<DragRunPreset, 2> DragRunPresets{DEFAULT_PRESET,MPH_PRESET};

#endif //DRAGY_CPP_DRAGRUNPRESETS_H
