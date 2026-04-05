#include "Shape.h"
#include "ShapeRenderer.h"
#include <cmath>

void Shape::draw() const {
    ShapeRenderer::draw(this);
}

Point2D Shape::getCenter() const {
    if (vertices.empty()) return {0.0f, 0.0f};
    
    float sumX = 0.0f;
    float sumY = 0.0f;
    
    for (int i = 0; i < vertices.size(); i++) {
        sumX += vertices[i].x;
        sumY += vertices[i].y;
    }
    
    float averageX = sumX / vertices.size();
    float averageY = sumY / vertices.size();
    
    return {averageX, averageY};
}

int Shape::getVertexIndexAt(float x, float y, float threshold) const {
    for (int i = 0; i < vertices.size(); i++) {
        float dx = vertices[i].x - x;
        float dy = vertices[i].y - y;
        float distance = std::sqrt(dx * dx + dy * dy);
        
        if (distance <= threshold) {
            return i;
        }
    }
    return -1; 
}

bool Shape::contains(float x, float y) const {
    if (vertices.empty()) return false;
    
    float minX = vertices[0].x;
    float maxX = vertices[0].x;
    float minY = vertices[0].y;
    float maxY = vertices[0].y;
    
    for (int i = 1; i < vertices.size(); i++) {
        if (vertices[i].x < minX) minX = vertices[i].x;
        if (vertices[i].x > maxX) maxX = vertices[i].x;
        if (vertices[i].y < minY) minY = vertices[i].y;
        if (vertices[i].y > maxY) maxY = vertices[i].y;
    }
    
    if (x >= minX && x <= maxX && y >= minY && y <= maxY) {
        return true;
    }
    return false;
}
