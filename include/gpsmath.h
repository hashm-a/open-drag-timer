//
// Created by Hashm A on 2026-04-22.
//

#ifndef DRAGY_CPP_GPSMATH_H
#define DRAGY_CPP_GPSMATH_H

#include <TinyGPSPlus.h>

#include "constants.h"
#include "types.h"

inline double GetDistanceBetweenInM(const Vector2 loc_one, const Vector2 loc_two) {
    return TinyGPSPlus::distanceBetween(loc_one.x,loc_one.y,loc_two.x,loc_two.y);
}

inline double GetDistanceBetweenInKM(const Vector2 loc_one, const Vector2 loc_two) {
    const auto dist_in_meters = GetDistanceBetweenInM(loc_one, loc_two);
    return dist_in_meters*M2KM; // CONVERT TO KM
}

inline double GetSlope(const double alt_one, const double alt_two, const Vector2 starting_loc, const Vector2 ending_loc) {
    const double distance_travelled = GetDistanceBetweenInM(starting_loc, ending_loc); // Use M for alt Calc
    if (distance_travelled == 0) {
        return 0.0;
    }
    return (alt_two-alt_one)/distance_travelled;
}

inline bool IsSlopeValid(const double slope) {
    return slope >= MAX_DOWNWARD_SLOPE;
}

inline bool IsSlopePercentValid(const double slope) {
    return IsSlopeValid(slope/100.0);
}

inline bool GetAndValidateSlope(const double alt_one, const double alt_two, const Vector2 starting_loc, const Vector2 ending_loc) {
    return IsSlopeValid(GetSlope(alt_one, alt_two, starting_loc, ending_loc));
}

#endif //DRAGY_CPP_MATH_H
