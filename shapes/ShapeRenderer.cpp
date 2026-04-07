#include "ShapeRenderer.h"
#include "DataClass.h"          // CRITICAL: Fixes C4430 and C2065
#include "Shape.h"
#include <QOpenGLFunctions_1_1>
#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>

void ShapeRenderer::draw(const Shape* shape) {
    if (!shape) return;

    auto gl = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_1_1>(QOpenGLContext::currentContext());
    if (gl == nullptr) return;

    if (!shape->get3D()) {
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
        
        return;
    }

    // Get the Triangulation DS
    DataClass mesh = shape->getGeneratedMesh();

    if (mesh.triangles.empty()) return;

    // --- 1. DRAW SOLID FACES ---
    gl->glColor3f(0.2f, 0.6f, 1.0f);
    gl->glBegin(GL_TRIANGLES);
    for (const auto& tri : mesh.triangles) {
        // Points for Corner 1
        gl->glVertex3f(tri.v1.x, tri.v1.y, tri.v1.z);
        // Points for Corner 2
        gl->glVertex3f(tri.v2.x, tri.v2.y, tri.v2.z);
        // Points for Corner 3
        gl->glVertex3f(tri.v3.x, tri.v3.y, tri.v3.z);
    }
    gl->glEnd();

    // --- 2. DRAW WIREFRAME (EDGES) ---
    gl->glLineWidth(1.0f);
    gl->glColor3f(1.0f, 1.0f, 1.0f);
    for (const auto& tri : mesh.triangles) {
        gl->glBegin(GL_LINE_LOOP);
        gl->glVertex3f(tri.v1.x, tri.v1.y, tri.v1.z);
        gl->glVertex3f(tri.v2.x, tri.v2.y, tri.v2.z);
        gl->glVertex3f(tri.v3.x, tri.v3.y, tri.v3.z);
        gl->glEnd();
    }

    // --- 3. DRAW VERTICES (POINTS) ---
    gl->glPointSize(6.0f);
    gl->glColor3f(1.0f, 0.3f, 0.3f);
    gl->glBegin(GL_POINTS);
    for (const auto& tri : mesh.triangles) {
        gl->glVertex3f(tri.v1.x, tri.v1.y, tri.v1.z);
        gl->glVertex3f(tri.v2.x, tri.v2.y, tri.v2.z);
        gl->glVertex3f(tri.v3.x, tri.v3.y, tri.v3.z);
    }
    gl->glEnd();
}