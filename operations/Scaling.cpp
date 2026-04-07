#include "Scaling.h"
#include <cmath>

// 2d
void Scaling::apply(Shape* shape, int selectedVertexIndex, Point2D currentGL, Point2D lastGL) {
    if (!shape || selectedVertexIndex == -1) return;

    auto& vertices = shape->getVertices();

    
    Point2D center = shape->getCenter();
    Point2D selected = vertices[selectedVertexIndex];

   
    Point2D fixed = {
        2 * center.x - selected.x,
        2 * center.y - selected.y
    };

  
    float oldDist = std::sqrt(
        (lastGL.x - fixed.x) * (lastGL.x - fixed.x) +
        (lastGL.y - fixed.y) * (lastGL.y - fixed.y)
    );

    float newDist = std::sqrt(
        (currentGL.x - fixed.x) * (currentGL.x - fixed.x) +
        (currentGL.y - fixed.y) * (currentGL.y - fixed.y)
    );

    if (oldDist < 0.001f) return;

    float scale = newDist / oldDist;

    for (auto& v : vertices) {
        v.x = fixed.x + (v.x - fixed.x) * scale;
        v.y = fixed.y + (v.y - fixed.y) * scale;
    }
}


// 3d
void Scaling::apply3D(Shape* shape, int selectedVertexIndex, Point2D currentGL, Point2D lastGL) {
    if (!shape || selectedVertexIndex == -1) return;

    auto& vertices = shape->getVertices();

    Point2D center = shape->getCenter();
    Point2D selected = vertices[selectedVertexIndex];

    Point2D fixed = {
        2 * center.x - selected.x,
        2 * center.y - selected.y
    };

    float oldDist = std::sqrt(
        (lastGL.x - fixed.x) * (lastGL.x - fixed.x) +
        (lastGL.y - fixed.y) * (lastGL.y - fixed.y)
    );

    float newDist = std::sqrt(
        (currentGL.x - fixed.x) * (currentGL.x - fixed.x) +
        (currentGL.y - fixed.y) * (currentGL.y - fixed.y)
    );

    if (oldDist < 0.001f) return;

    float scale = newDist / oldDist;

    for (auto& v : vertices) {
        v.x = fixed.x + (v.x - fixed.x) * scale;
        v.y = fixed.y + (v.y - fixed.y) * scale;
    }


    if (shape->get3D()) {
        shape->setDepth(shape->getDepth() * scale);
    }
}