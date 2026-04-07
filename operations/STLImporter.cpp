#include "STLImporter.h"
#include <fstream>
#include <iostream>
#include <map>

struct VertexCompare {
    bool operator()(const Vertex3D& a, const Vertex3D& b) const {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    }
};

bool STLImporter::importFromAsciiSTL(const std::string& filename, DataClass& meshData) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not opened\n";
        return false;
    }

    std::string word;
    std::vector<Vertex3D> temp;
    std::map<Vertex3D, unsigned int, VertexCompare> vertexToIndexMap;
    unsigned int nextIndex = 0;

    while (file >> word) {
        if (word == "vertex") {
            Vertex3D v;
            file >> v.x >> v.y >> v.z;

            if (vertexToIndexMap.find(v) == vertexToIndexMap.end()) {
                vertexToIndexMap[v] = nextIndex;
                nextIndex++;
            }

            temp.push_back(v);

            if (temp.size() == 3) {
                Triangle3D t;
                t.v1 = temp[0];
                t.v2 = temp[1];
                t.v3 = temp[2];

                meshData.triangles.push_back(t);
                temp.clear();
            }
        }
    }
    
    return true;
}
