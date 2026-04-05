#include "ShapeRenderer.h"
#include <QOpenGLFunctions_1_1>
#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>

void ShapeRenderer::draw(const Shape* shape) {
    if (!shape) return;
    
    // Qt requires us to get the OpenGL tools before we can draw our shapes
    auto gl = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_1_1>(QOpenGLContext::currentContext());
    if (gl == nullptr) return;
    
    if (!shape->get3D()) {
        draw2D(shape, gl);
    } else {
        draw3D(shape, gl);
    }
}

void ShapeRenderer::draw2D(const Shape* shape, QOpenGLFunctions_1_1* gl) {
    const auto& vertices = shape->getVerticesConst();
    
    gl->glColor3f(0.2f, 0.6f, 1.0f);
    gl->glBegin(GL_POLYGON);
    for (int i = 0; i < vertices.size(); i++) {
        gl->glVertex2f(vertices[i].x, vertices[i].y);
    }
    gl->glEnd();

    gl->glColor3f(1.0f, 1.0f, 1.0f);
    gl->glLineWidth(2.0f);
    gl->glBegin(GL_LINE_LOOP);
    for (int i = 0; i < vertices.size(); i++) {
        gl->glVertex2f(vertices[i].x, vertices[i].y);
    }
    gl->glEnd();

    gl->glPointSize(8.0f);
    gl->glColor3f(1.0f, 0.4f, 0.4f);
    gl->glBegin(GL_POINTS);
    for (int i = 0; i < vertices.size(); i++) {
        gl->glVertex2f(vertices[i].x, vertices[i].y);
    }
    gl->glEnd();
}

void ShapeRenderer::draw3D(const Shape* shape, QOpenGLFunctions_1_1* gl) {
    float zFront = shape->getDepth() / 2.0f;
    float zBack = -shape->getDepth() / 2.0f;

    draw3DFrontFace(shape, gl, zFront);
    draw3DBackFace(shape, gl, zBack);
    draw3DSides(shape, gl, zFront, zBack);
    draw3DEdges(shape, gl, zFront, zBack);
}

void ShapeRenderer::draw3DFrontFace(const Shape* shape, QOpenGLFunctions_1_1* gl, float zFront) {
    const auto& vertices = shape->getVerticesConst();
    // Front Face
    gl->glColor3f(1.0f, 1.0f, 1.0f);
    gl->glBegin(GL_POLYGON);
    for (int i = 0; i < vertices.size(); i++) {
        gl->glVertex3f(vertices[i].x, vertices[i].y, zFront);
    }
    gl->glEnd();
}

void ShapeRenderer::draw3DBackFace(const Shape* shape, QOpenGLFunctions_1_1* gl, float zBack) {
    const auto& vertices = shape->getVerticesConst();
    // Back Face
    gl->glColor3f(0.5f, 0.5f, 0.5f);
    gl->glBegin(GL_POLYGON);
    for (int i = (int)vertices.size() - 1; i >= 0; i--) {
        gl->glVertex3f(vertices[i].x, vertices[i].y, zBack);
    }
    gl->glEnd();
}

void ShapeRenderer::draw3DSides(const Shape* shape, QOpenGLFunctions_1_1* gl, float zFront, float zBack) {
    const auto& vertices = shape->getVerticesConst();
    // Sides
    gl->glBegin(GL_QUADS);
    for (int i = 0; i < vertices.size(); i++) {
        if (i == 0) gl->glColor3f(1.0f, 0.0f, 0.0f);
        else if (i == 1) gl->glColor3f(0.0f, 1.0f, 0.0f);
        else if (i == 2) gl->glColor3f(0.0f, 0.0f, 1.0f);
        else if (i == 3) gl->glColor3f(1.0f, 1.0f, 0.0f);
        else gl->glColor3f(1.0f, 0.0f, 1.0f);
        
        int next = i + 1;
        if (next >= vertices.size()) {
            next = 0;
        }
        
        float currentX = vertices[i].x;
        float currentY = vertices[i].y;
        float nextX = vertices[next].x;
        float nextY = vertices[next].y;
        
        gl->glVertex3f(currentX, currentY, zFront);
        gl->glVertex3f(nextX, nextY, zFront);
        gl->glVertex3f(nextX, nextY, zBack);
        gl->glVertex3f(currentX, currentY, zBack);
    }
    gl->glEnd();
}

void ShapeRenderer::draw3DEdges(const Shape* shape, QOpenGLFunctions_1_1* gl, float zFront, float zBack) {
    const auto& vertices = shape->getVerticesConst();
    // Edges
    gl->glColor3f(1.0f, 1.0f, 1.0f);
    gl->glLineWidth(2.0f);
    
    gl->glBegin(GL_LINE_LOOP);
    for (int i = 0; i < vertices.size(); i++) {
        gl->glVertex3f(vertices[i].x, vertices[i].y, zFront);
    }
    gl->glEnd();

    gl->glBegin(GL_LINE_LOOP);
    for (int i = 0; i < vertices.size(); i++) {
        gl->glVertex3f(vertices[i].x, vertices[i].y, zBack);
    }
    gl->glEnd();

    gl->glBegin(GL_LINES);
    for (int i = 0; i < vertices.size(); i++) {
        gl->glVertex3f(vertices[i].x, vertices[i].y, zFront);
        gl->glVertex3f(vertices[i].x, vertices[i].y, zBack);
    }
    gl->glEnd();
    
    // Vertices
    gl->glPointSize(8.0f);
    gl->glColor3f(1.0f, 0.4f, 0.4f);
    gl->glBegin(GL_POINTS);
    for (int i = 0; i < vertices.size(); i++) {
        gl->glVertex3f(vertices[i].x, vertices[i].y, zFront);
        gl->glVertex3f(vertices[i].x, vertices[i].y, zBack);
    }
    gl->glEnd();
}
