#include "MeshExtruder.h"
#include <cmath>

DataClass MeshExtruder::extrude(const std::vector<Point2D>& pts, float d, bool isSphere) {
    DataClass m;
    int n = pts.size();
    if (n < 3) return m;

    // center
    float cx = 0, cy = 0;
    for (auto& p : pts) {
        cx += p.x;
        cy += p.y;
    }
    cx /= n; cy /= n;

    // if (isSphere) {
    //     float r = 0;
    //     if (n > 0) {
    //         float dx = pts[0].x - cx;
    //         float dy = pts[0].y - cy;
    //         r = std::sqrt(dx*dx + dy*dy);
    //     }
    //     if (r == 0) r = d / 2.0f;

    //     int sectors = 30;
    //     int stacks = 15;
    //     float pi = 3.1415926535f;
    //     std::vector<Vertex3D> sv;
    //     for(int i = 0; i <= stacks; ++i) {
    //         float phi = i * pi / stacks;
    //         for(int j = 0; j <= sectors; ++j) {
    //             float theta = j * 2.0f * pi / sectors;
    //             float x = cx + r * cos(theta) * sin(phi);
    //             float y = cy + r * sin(theta) * sin(phi);
    //             float z = r * cos(phi);
    //             sv.push_back({x, y, z});
    //         }
    //     }

    //     for(int i = 0; i < stacks; ++i) {
    //         for(int j = 0; j < sectors; ++j) {
    //             int first = (i * (sectors + 1)) + j;
    //             int second = first + sectors + 1;

    //             Vertex3D v1 = sv[first];
    //             Vertex3D v2 = sv[second];
    //             Vertex3D v3 = sv[first + 1];
    //             Vertex3D v4 = sv[second + 1];

    //             m.triangles.push_back({v1, v2, v3});
    //             m.triangles.push_back({v2, v4, v3});
    //         }
    //     }
    //     return m;
    // }

    float zt = d / 2.0f, zb = -d / 2.0f;
    Vertex3D tc = {cx, cy, zt};
    Vertex3D bc = {cx, cy, zb};

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;

        Vertex3D t1 = {pts[i].x, pts[i].y, zt};
        Vertex3D t2 = {pts[j].x, pts[j].y, zt};
        Vertex3D b1 = {pts[i].x, pts[i].y, zb};
        Vertex3D b2 = {pts[j].x, pts[j].y, zb};

        // top
        m.triangles.push_back({t1, t2, tc});

        // bottom
        m.triangles.push_back({b1, bc, b2});

        // sides
        m.triangles.push_back({t1, b1, t2});
        m.triangles.push_back({t2, b1, b2});
    }

    return m;
}
