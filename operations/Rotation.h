#ifndef ROTATION_H
#define ROTATION_H

#include "Shape.h"

class Rotation {
public:
    static void apply(Shape* shape, float angle);
    static void apply3D(float& xRot, float& yRot, int dx, int dy);
};

#endif
