#ifndef DATACLASS_H
#define DATACLASS_H

#include <vector>
#include <string>

struct Vertex3D {
    float x, y, z;
};

struct Triangle3D {
    Vertex3D v1, v2, v3;
};

class DataClass {
public:
    std::vector<Triangle3D> triangles;

    void loadSTL(std::string filename);
    bool exportSTL(std::string filename) const;
};

#endif // DATACLASS_H
