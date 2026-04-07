#include "Translation.h"

void Translation::apply(Shape* shape, float dx, float dy) {
    if (!shape) return;
    
    std::vector<Point2D>& points = shape->getVertices();
    for (int i = 0; i < points.size(); i++) {
        points[i].x += dx;
        points[i].y += dy;
    }
}

void Translation::apply3D(Shape* shape, float dx, float dy, float dz) {
    if (!shape) return;
    
    // For our 2.5D shapes, X and Y translation moves the base shape
    apply(shape, dx, dy);
    
    // Z translation isn't explicitly stored as a position offset in Shape right now, 
    // but the stub is here for future architectural expansion.
}
