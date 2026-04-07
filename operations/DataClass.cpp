#include "DataClass.h"
#include <fstream>
#include <iostream>
#include <set>

struct VertexCompare {
    bool operator()(const Vertex3D& a, const Vertex3D& b) const {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    }
};

void DataClass::loadSTL(std::string filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not opened\n";
        return;
    }

    std::string word;
    std::vector<Vertex3D> temp;
    std::set<Vertex3D, VertexCompare> uniqueVertices;

    while (file >> word) {

        if (word == "vertex") {
            Vertex3D v;
            file >> v.x >> v.y >> v.z;

            // avoid duplicate vertices
            auto it = uniqueVertices.find(v);
            if (it == uniqueVertices.end()) {
                uniqueVertices.insert(v);
            }
            else {
                v = *it;
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
}          