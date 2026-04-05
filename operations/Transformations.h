#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "Shape.h"

void TranslateShape(Shape* shape, float dx, float dy);
void ScaleShape(Shape* shape, float factor);
void ScaleShapeByDrag(Shape* shape, float oldX, float oldY, float newX, float newY);

#endif
