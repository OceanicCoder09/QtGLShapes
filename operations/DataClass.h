#ifndef DATACLASS_H
#define DATACLASS_H

#include <vector>
#include <string>
#include "Vertex3D.h"
#include "Triangle3D.h"

class DataClass {
public:
    std::vector<Triangle3D> triangles;

    void loadSTL(std::string filename);
};

#endif // DATACLASS_H
