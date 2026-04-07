#ifndef SCALING_H
#define SCALING_H

#include "Shape.h"
#include <cmath>

class Scaling {
public:
    static void apply(Shape* shape, int selectedVertexIndex, Point2D currentGL, Point2D lastGL);
    static void apply3D(Shape* shape, int selectedVertexIndex, Point2D currentGL, Point2D lastGL);
};

#endif
