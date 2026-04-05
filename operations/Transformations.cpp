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

void ScaleShape(Shape* shape, float factor) {
    if (!shape) return;
    
    Point2D center = shape->getCenter();
    std::vector<Point2D>& points = shape->getVertices();
    
    for (int i = 0; i < points.size(); i++) {
        float dist_x = points[i].x - center.x;
        float dist_y = points[i].y - center.y;
        
        points[i].x = center.x + (dist_x * factor);
        points[i].y = center.y + (dist_y * factor);
    }
    
    if (shape->get3D()) {
        shape->setDepth(shape->getDepth() * factor);
    }
}

void ScaleShapeByDrag(Shape* shape, float oldX, float oldY, float newX, float newY) {
    if (!shape) return;
    
    Point2D center = shape->getCenter();
    
    float dxOld = oldX - center.x;
    float dyOld = oldY - center.y;
    float oldDist = std::sqrt(dxOld * dxOld + dyOld * dyOld);
    
    float dxNew = newX - center.x;
    float dyNew = newY - center.y;
    float newDist = std::sqrt(dxNew * dxNew + dyNew * dyNew);
    
    if (oldDist > 0.001f) {
        float factor = newDist / oldDist;
        ScaleShape(shape, factor);
    }
}


