//
// Created by Hashm A on 2026-04-22.
//

#ifndef DRAGY_CPP_GPSMATH_H
#define DRAGY_CPP_GPSMATH_H

#include <TinyGPSPlus.h>

#include "constants.h"
#include "types.h"

inline double GetDistanceBetweenInM(Vector2 loc_one, Vector2 loc_two) {
    auto dist_in_meters = TinyGPSPlus::distanceBetween(loc_one.x,loc_one.y,loc_two.x,loc_two.y);
    return dist_in_meters;
}

inline double GetDistanceBetweenInKM(Vector2 loc_one, Vector2 loc_two) {
    auto dist_in_meters = GetDistanceBetweenInM(loc_one, loc_two);
    return dist_in_meters*M2KM; // CONVERT TO KM
}

inline double GetSlope(int alt_one, int alt_two, Vector2 starting_loc, Vector2 ending_loc) {
    return (alt_two-alt_one)/GetDistanceBetweenInM(starting_loc, ending_loc); // Use M for alt Calc
}

#endif //DRAGY_CPP_MATH_H
