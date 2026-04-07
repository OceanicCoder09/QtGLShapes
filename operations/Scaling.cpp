#include "Scaling.h"

void Scaling::apply(Shape* shape, int selectedVertexIndex, Point2D currentGL, Point2D lastGL) {
    if (!shape || selectedVertexIndex == -1) return;

    Point2D center = shape->getCenter();
    Point2D selectedPos = shape->getVertices()[selectedVertexIndex];
    Point2D fixedPoint = { 2.0f * center.x - selectedPos.x, 2.0f * center.y - selectedPos.y };
    
    float dxOld = lastGL.x - fixedPoint.x;
    float dyOld = lastGL.y - fixedPoint.y;
    float oldDist = std::sqrt(dxOld*dxOld + dyOld*dyOld);
    
    float dxNew = currentGL.x - fixedPoint.x;
    float dyNew = currentGL.y - fixedPoint.y;
    float newDist = std::sqrt(dxNew*dxNew + dyNew*dyNew);
    
    if (oldDist > 0.001f) {
        float factor = newDist / oldDist;
        for (auto& v : shape->getVertices()) {
            v.x = fixedPoint.x + (v.x - fixedPoint.x) * factor;
            v.y = fixedPoint.y + (v.y - fixedPoint.y) * factor;
        }
    }
}

void Scaling::apply3D(Shape* shape, int selectedVertexIndex, Point2D currentGL, Point2D lastGL) {
    if (!shape || selectedVertexIndex == -1) return;

    Point2D center = shape->getCenter();
    Point2D selectedPos = shape->getVertices()[selectedVertexIndex];
    Point2D fixedPoint = { 2.0f * center.x - selectedPos.x, 2.0f * center.y - selectedPos.y };
    
    float dxOld = lastGL.x - fixedPoint.x;
    float dyOld = lastGL.y - fixedPoint.y;
    float oldDist = std::sqrt(dxOld*dxOld + dyOld*dyOld);
    
    float dxNew = currentGL.x - fixedPoint.x;
    float dyNew = currentGL.y - fixedPoint.y;
    float newDist = std::sqrt(dxNew*dxNew + dyNew*dyNew);
    
    if (oldDist > 0.001f) {
        float factor = newDist / oldDist;
        for (auto& v : shape->getVertices()) {
            v.x = fixedPoint.x + (v.x - fixedPoint.x) * factor;
            v.y = fixedPoint.y + (v.y - fixedPoint.y) * factor;
        }
        if (shape->get3D()) {
            shape->setDepth(shape->getDepth() * factor);
        }
    }
}
