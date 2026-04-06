#include "DataClass.h"
#include <fstream>
#include <iostream>
#include <cmath>

void DataClass::loadSTL(std::string filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not opened\n";
        return;
    }

    std::string word;
    std::vector<Vertex3D> temp;
    std::vector<Vertex3D> uniqueVertices;

    while (file >> word) {

        if (word == "vertex") {
            Vertex3D v;
            file >> v.x >> v.y >> v.z;

            bool found = false;
            for (auto &u : uniqueVertices) {
                if (u.x == v.x && u.y == v.y && u.z == v.z) {
                    v = u;
                    found = true;
                    break;
                }
            }

            if (!found) {
                uniqueVertices.push_back(v);
            }

            temp.push_back(v);

            if (temp.size() == 3) {
                Triangle3D t;
                t.v1 = temp[0];
                t.v2 = temp[1];
                t.v3 = temp[2];

                triangles.push_back(t);
                temp.clear();
            }
        }
    }

    std::cout << "Total triangles: " << triangles.size() << std::endl;
    std::cout << "Unique vertices: " << uniqueVertices.size() << std::endl;
}

bool DataClass::exportSTL(std::string filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Failed to open file for STL export: " << filename << std::endl;
        return false;
    }

    out << "solid generated_mesh\n";
    for (const auto& tri : triangles) {
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
