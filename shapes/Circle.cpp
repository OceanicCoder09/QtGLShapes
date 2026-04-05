#include "Circle.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Circle::Circle() {
    int numPoints = 60; // Smooth circle
    float radius = 0.4f;
    for (int i = 0; i < numPoints; ++i) {
        float angle = i * 2.0f * M_PI / numPoints;
        vertices.push_back({radius * std::cos(angle), radius * std::sin(angle)});
    }
}
