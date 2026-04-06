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
