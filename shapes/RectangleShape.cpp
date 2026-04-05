#include "RectangleShape.h"

RectangleShape::RectangleShape() {
    vertices.push_back({-0.6f, 0.3f});
    vertices.push_back({-0.6f, -0.3f});
    vertices.push_back({0.6f, -0.3f});
    vertices.push_back({0.6f, 0.3f});
}
