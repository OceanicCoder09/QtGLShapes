#ifndef MESH_EXTRUDER_H
#define MESH_EXTRUDER_H

#include <vector>
#include "../shapes/Shape.h"
#include "DataClass.h"

class MeshExtruder {
public:
    static DataClass extrude(const std::vector<Point2D>& baseVertices, float depth, bool isSphere = false);
};

#endif // MESH_EXTRUDER_H
