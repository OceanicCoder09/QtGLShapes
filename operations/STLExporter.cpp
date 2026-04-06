#include "STLExporter.h"
#include <fstream>
#include <iostream>
#include <cmath>

bool STLExporter::exportToAsciiSTL(const DataClass& meshData, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Failed to open file for STL export: " << filename << std::endl;
        return false;
    }

    out << "solid generated_mesh\n";
    for (const auto& tri : meshData.triangles) {
        const Vertex3D& v1 = tri.v1;
        const Vertex3D& v2 = tri.v2;
        const Vertex3D& v3 = tri.v3;

        // Normal calculation using cross product
        float ux = v2.x - v1.x;
        float uy = v2.y - v1.y;
        float uz = v2.z - v1.z;

        float vx = v3.x - v1.x;
        float vy = v3.y - v1.y;
        float vz = v3.z - v1.z;

        float nx = uy * vz - uz * vy;
        float ny = uz * vx - ux * vz;
        float nz = ux * vy - uy * vx;

        float length = std::sqrt(nx * nx + ny * ny + nz * nz);
        if (length > 1e-6f) {
            nx /= length; ny /= length; nz /= length;
        } else {
            nx = 0.0f; ny = 0.0f; nz = 1.0f; // fallback normal
        }

        out << "  facet normal " << nx << " " << ny << " " << nz << "\n";
        out << "    outer loop\n";
        out << "      vertex " << v1.x << " " << v1.y << " " << v1.z << "\n";
        out << "      vertex " << v2.x << " " << v2.y << " " << v2.z << "\n";
        out << "      vertex " << v3.x << " " << v3.y << " " << v3.z << "\n";
        out << "    endloop\n";
        out << "  endfacet\n";
    }
    out << "endsolid generated_mesh\n";

    return true;
}
