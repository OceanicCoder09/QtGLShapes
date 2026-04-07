#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape {
public:
    Circle();
    virtual DataClass getGeneratedMesh() const override;
};

#endif // CIRCLE_H
