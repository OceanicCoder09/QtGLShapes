#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include "Shape.h"

class QOpenGLFunctions_1_1;

class ShapeRenderer {
public:
    static void draw(const Shape* shape);
private:
    static void draw2D(const Shape* shape, QOpenGLFunctions_1_1* gl);
    static void draw3D(const Shape* shape, QOpenGLFunctions_1_1* gl);
    static void draw3DSphere(const Shape* shape, QOpenGLFunctions_1_1* gl);
    
    static void draw3DFrontFace(const Shape* shape, QOpenGLFunctions_1_1* gl, float zFront);
    static void draw3DBackFace(const Shape* shape, QOpenGLFunctions_1_1* gl, float zBack);
    static void draw3DSides(const Shape* shape, QOpenGLFunctions_1_1* gl, float zFront, float zBack);
    static void draw3DEdges(const Shape* shape, QOpenGLFunctions_1_1* gl, float zFront, float zBack);
};

#endif // SHAPE_RENDERER_H
