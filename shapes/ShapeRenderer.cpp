#include "ShapeRenderer.h"
#include <QOpenGLFunctions_1_1>
#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>
#include <cmath>
#include "Circle.h"

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
    if (dynamic_cast<const Circle*>(shape)) {
        draw3DSphere(shape, gl);
        return;
    }

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

void ShapeRenderer::draw3DSphere(const Shape* shape, QOpenGLFunctions_1_1* gl) {
    const auto& vertices = shape->getVerticesConst();
    if (vertices.empty()) return;

    float cx = 0, cy = 0;
    for (const auto& v : vertices) { 
        cx += v.x; 
        cy += v.y; 
    }
    cx /= vertices.size();
    cy /= vertices.size();

    float dx = vertices[0].x - cx;
    float dy = vertices[0].y - cy;
    float r = std::sqrt(dx*dx + dy*dy);
    if (r == 0) r = shape->getDepth() / 2.0f;

    int sectors = 30;
    int stacks = 15;
    float pi = 3.1415926535f;

    // Solid Sphere
    gl->glColor3f(0.2f, 0.6f, 1.0f);
    gl->glBegin(GL_QUADS);
    for(int i = 0; i < stacks; ++i) {
        float phi1 = i * pi / stacks;
        float phi2 = (i + 1) * pi / stacks;
        for(int j = 0; j < sectors; ++j) {
            float theta1 = j * 2.0f * pi / sectors;
            float theta2 = (j + 1) * 2.0f * pi / sectors;

            float x1 = cx + r * std::cos(theta1) * std::sin(phi1);
            float y1 = cy + r * std::sin(theta1) * std::sin(phi1);
            float z1 = r * std::cos(phi1);

            float x2 = cx + r * std::cos(theta2) * std::sin(phi1);
            float y2 = cy + r * std::sin(theta2) * std::sin(phi1);
            float z2 = r * std::cos(phi1);

            float x3 = cx + r * std::cos(theta2) * std::sin(phi2);
            float y3 = cy + r * std::sin(theta2) * std::sin(phi2);
            float z3 = r * std::cos(phi2);

            float x4 = cx + r * std::cos(theta1) * std::sin(phi2);
            float y4 = cy + r * std::sin(theta1) * std::sin(phi2);
            float z4 = r * std::cos(phi2);

            gl->glVertex3f(x1, y1, z1);
            gl->glVertex3f(x2, y2, z2);
            gl->glVertex3f(x3, y3, z3);
            gl->glVertex3f(x4, y4, z4);
        }
    }
    gl->glEnd();

    // Wireframe overlay for 3D visibility
    gl->glColor3f(1.0f, 1.0f, 1.0f);
    gl->glLineWidth(1.0f);
    for(int i = 0; i <= stacks; ++i) {
        float phi = i * pi / stacks;
        gl->glBegin(GL_LINE_LOOP);
        for(int j = 0; j < sectors; ++j) {
            float theta = j * 2.0f * pi / sectors;
            float x = cx + r * std::cos(theta) * std::sin(phi);
            float y = cy + r * std::sin(theta) * std::sin(phi);
            float z = r * std::cos(phi);
            gl->glVertex3f(x, y, z);
        }
        gl->glEnd();
    }
}
