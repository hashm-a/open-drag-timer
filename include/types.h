//
// Created by Hashm A on 2026-04-19.
//

#ifndef DRAGY_CPP_TYPES_H
#define DRAGY_CPP_TYPES_H

struct Vector2 {
    double x = 0.0;
    double y = 0.0;

    Vector2() {
        x=0.0;
        y=0.0;
    }

    Vector2(const double new_x, const double new_y) {
        x = new_x;
        y = new_y;
    }
};

#endif //DRAGY_CPP_TYPES_H
