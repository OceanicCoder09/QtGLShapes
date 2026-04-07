#include "Rotation.h"
#include <cmath>

void Rotation::apply(Shape* shape, float angle) {
    if (!shape) return;
    
    Point2D center = shape->getCenter();
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    
    for (auto& v : shape->getVertices()) {
        float dx = v.x - center.x;
        float dy = v.y - center.y;
        v.x = center.x + (dx * cosA - dy * sinA);
        v.y = center.y + (dx * sinA + dy * cosA);
    }
}

void Rotation::apply3D(float& xRot, float& yRot, int dx, int dy) {
    xRot += dy * 0.5f;
    yRot += dx * 0.5f;
}
