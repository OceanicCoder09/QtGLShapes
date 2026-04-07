#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "DataClass.h" // Added so the compiler knows what a mesh is

struct Point2D {
    float x, y;
};

class Shape {
public:
    virtual ~Shape() = default;
    
    virtual void draw() const;

    // Added this virtual function so the Renderer can call it
    virtual DataClass getGeneratedMesh() const;

    bool contains(float x, float y) const;
    int getVertexIndexAt(float x, float y, float threshold = 0.05f) const;
    Point2D getCenter() const;

    void set3D(bool enable, float zDepth = 0.5f) { is3D = enable; depth = zDepth; }
    bool get3D() const { return is3D; }

    float getDepth() const { return depth; }
    void setDepth(float zDepth) { depth = zDepth; }

    std::vector<Point2D>& getVertices() { return vertices; }
    const std::vector<Point2D>& getVerticesConst() const { return vertices; }

protected:
    std::vector<Point2D> vertices;
    bool is3D = false;
    float depth = 0.5f;
};

#endif