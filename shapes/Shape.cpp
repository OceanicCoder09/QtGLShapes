#include "Shape.h"
#include "ShapeRenderer.h"
#include "MeshExtruder.h" // Added to perform the 3D triangulation
#include <cmath>

void Shape::draw() const {
    ShapeRenderer::draw(this);
}

// Added implementation: This builds the DS for the Renderer
DataClass Shape::getGeneratedMesh() const {
    // If it's not 3D, we can still return a 'flat' mesh with 0 depth
    float d = is3D ? depth : 0.0f;
    
    // We pass 'false' for isSphere by default. 
    // Specific classes like Circle can override this if needed.
    return MeshExtruder::extrude(vertices, d, false);
}

Point2D Shape::getCenter() const {
    if (vertices.empty()) return {0.0f, 0.0f};
    
    float sumX = 0.0f;
    float sumY = 0.0f;
    
    for (size_t i = 0; i < vertices.size(); i++) {
        sumX += vertices[i].x;
        sumY += vertices[i].y;
    }
    
    return {sumX / vertices.size(), sumY / vertices.size()};
}

int Shape::getVertexIndexAt(float x, float y, float threshold) const {
    for (int i = 0; i < (int)vertices.size(); i++) {
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
    
    float minX = vertices[0].x, maxX = vertices[0].x;
    float minY = vertices[0].y, maxY = vertices[0].y;
    
    for (size_t i = 1; i < vertices.size(); i++) {
        if (vertices[i].x < minX) minX = vertices[i].x;
        if (vertices[i].x > maxX) maxX = vertices[i].x;
        if (vertices[i].y < minY) minY = vertices[i].y;
        if (vertices[i].y > maxY) maxY = vertices[i].y;
    }
    
    return (x >= minX && x <= maxX && y >= minY && y <= maxY);
}