#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "Shape.h"

class Translation {
public:
    static void apply(Shape* shape, float dx, float dy);
    static void apply3D(Shape* shape, float dx, float dy, float dz);
};

#endif
