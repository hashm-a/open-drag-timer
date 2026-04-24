//
// Created by Hashm A on 2026-04-22.
//

#ifndef DRAGY_CPP_GPSMATH_H
#define DRAGY_CPP_GPSMATH_H

#include "constants.h"
#include "TinyGPSPlus.h"
#include "types.h"

inline double GetDistanceBetween(Vector2 loc_one, Vector2 loc_two) {
    auto dist_in_meters = TinyGPSPlus::distanceBetween(loc_one.x,loc_one.y,loc_two.x,loc_two.y);
    return dist_in_meters*M2KM; // CONVERT TO KM
}

inline double GetSlope(int alt_one, int alt_two, Vector2 starting_loc, Vector2 ending_loc) {
    return (alt_two-alt_one)/(GetDistanceBetween(starting_loc, ending_loc) * KM2M); // Convert back to M for alt calc
}

#endif //DRAGY_CPP_MATH_H
