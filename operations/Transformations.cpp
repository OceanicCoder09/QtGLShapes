#include "Transformations.h"
#include <cmath>

void TranslateShape(Shape* shape, float dx, float dy) {
    if (!shape) return;
    
    std::vector<Point2D>& points = shape->getVertices();
    for (int i = 0; i < points.size(); i++) {
        points[i].x += dx;
        points[i].y += dy;
    }
}


