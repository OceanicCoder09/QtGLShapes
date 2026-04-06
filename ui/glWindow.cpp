#include "glWindow.h"
#include <QMouseEvent>
#include <cmath>
#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_1_1>
#include <QOpenGLContext>
#include "Triangle.h"
#include "Square.h"
#include "RectangleShape.h"
#include "Circle.h"
#include "Transformations.h"
#include "MeshExtruder.h"
#include "STLExporter.h"

glWindow::glWindow(QWidget *parent)
    : QOpenGLWidget(parent), currentShape(nullptr), isDragging(false), isScaling(false), isRotating(false), selectedVertexIndex(-1), xRot(30.0f), yRot(-30.0f), pendingShapeType(0) {
    setFocusPolicy(Qt::StrongFocus);
}

glWindow::~glWindow() {
    if (currentShape != nullptr) {
        delete currentShape;
    }
}

void glWindow::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.15f, 0.15f, 0.20f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void glWindow::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void glWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (currentShape != nullptr) {
        auto gl = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_1_1>(QOpenGLContext::currentContext());
        if (gl && currentShape->get3D()) {
            gl->glPushMatrix();
            // Rotate the view based on mouse dragging
            gl->glRotatef(xRot, 1.0f, 0.0f, 0.0f);
            gl->glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        }
        
        currentShape->draw();
        
        if (gl && currentShape->get3D()) {
            gl->glPopMatrix();
        }
    }
}

void glWindow::setPendingShapeType(int type) {
    pendingShapeType = type;
}

void glWindow::clearShape() {
    if (currentShape != nullptr) {
        delete currentShape;
        currentShape = nullptr;
    }
    update(); 
}

void glWindow::convertTo3D() {
    if (currentShape != nullptr && !currentShape->get3D()) {
        currentShape->set3D(true);
        update();
    }
}

bool glWindow::exportToSTL(const QString& filePath) {
    if (currentShape == nullptr) return false;
    
    // Extrude the current 2D shape using its set depth
    // If it's a 2D shape being exported, we can just give it a default depth (e.g. 0.5f)
    float depth = currentShape->get3D() ? currentShape->getDepth() : 0.5f;
    bool isSphere = (dynamic_cast<Circle*>(currentShape) != nullptr);
    DataClass mesh = MeshExtruder::extrude(currentShape->getVertices(), depth, isSphere);
    
    // Export the constructed mesh
    return STLExporter::exportToAsciiSTL(mesh, filePath.toStdString());
}

Point2D glWindow::mapToGL(int x, int y) {
    float normalized_x = (2.0f * x / width()) - 1.0f;
    float normalized_y = 1.0f - (2.0f * y / height());
    return {normalized_x, normalized_y};
}

void glWindow::mousePressEvent(QMouseEvent *event) {
    Point2D glPos = mapToGL(event->pos().x(), event->pos().y());
    
    if (event->button() == Qt::RightButton && currentShape != nullptr && currentShape->get3D()) {
        isRotating = true;
        lastMousePos = event->pos();
        return;
    }
    
    if (event->button() == Qt::LeftButton) {
        if (currentShape != nullptr) {
            int cornerIndex = currentShape->getVertexIndexAt(glPos.x, glPos.y, 0.05f);
            if (cornerIndex != -1) {
                isScaling = true;
                selectedVertexIndex = cornerIndex;
                isDragging = false;
                lastMousePos = event->pos();
                return;
            }

            if (currentShape->contains(glPos.x, glPos.y)) {
                isDragging = true;
                isScaling = false;
                lastMousePos = event->pos();
                return;
            }
            
            if (currentShape->get3D()) {
                // In 3D mode we do relaxed picking
                Point2D center = currentShape->getCenter();
                float dx = center.x - glPos.x;
                float dy = center.y - glPos.y;
                float distance = std::sqrt(dx*dx + dy*dy);
                
                if (distance < 0.8f) { 
                    if (distance > 0.3f) { // If far from center, scale.
                        isScaling = true;
                        isDragging = false;
                    } else { // If near center, drag.
                        isDragging = true;
                        isScaling = false;
                    }
                    lastMousePos = event->pos();
                    return;
                }
            }
        }
        
        // Prevent deleting current 3D shape when missing
        if (currentShape != nullptr && currentShape->get3D()) {
            return;
        }
        
        //  shape exactly where user clicked 
        if (currentShape != nullptr) {
            delete currentShape;
        }
        
        if (pendingShapeType == 0) {
            currentShape = new Triangle();
        } else if (pendingShapeType == 1) {
            currentShape = new Square();
        } else if (pendingShapeType == 2) {
            currentShape = new RectangleShape();
        } else if (pendingShapeType == 3) {
            currentShape = new Circle();
        }
        
        TranslateShape(currentShape, glPos.x, glPos.y);
        update(); 
    }
}

void glWindow::mouseMoveEvent(QMouseEvent *event) {
    if (currentShape == nullptr) return;

    if (isRotating) {
        int dx = event->pos().x() - lastMousePos.x();
        int dy = event->pos().y() - lastMousePos.y();
        
        xRot += dy * 0.5f;
        yRot += dx * 0.5f;
        
        lastMousePos = event->pos();
        update();
    } else if (isScaling && selectedVertexIndex != -1) {
        Point2D currentGL = mapToGL(event->pos().x(), event->pos().y());
        Point2D lastGL = mapToGL(lastMousePos.x(), lastMousePos.y());
        
        Point2D center = currentShape->getCenter();
        Point2D selectedPos = currentShape->getVertices()[selectedVertexIndex];
        Point2D fixedPoint = { 2.0f * center.x - selectedPos.x, 2.0f * center.y - selectedPos.y };
        
        float dxOld = lastGL.x - fixedPoint.x;
        float dyOld = lastGL.y - fixedPoint.y;
        float oldDist = std::sqrt(dxOld*dxOld + dyOld*dyOld);
        
        float dxNew = currentGL.x - fixedPoint.x;
        float dyNew = currentGL.y - fixedPoint.y;
        float newDist = std::sqrt(dxNew*dxNew + dyNew*dyNew);
        
        if (oldDist > 0.001f) {
            float factor = newDist / oldDist;
            for (auto& v : currentShape->getVertices()) {
                v.x = fixedPoint.x + (v.x - fixedPoint.x) * factor;
                v.y = fixedPoint.y + (v.y - fixedPoint.y) * factor;
            }
            if (currentShape->get3D()) {
                currentShape->setDepth(currentShape->getDepth() * factor);
            }
        }
        
        lastMousePos = event->pos();
        update();
    } else if (isDragging) {
        Point2D currentGL = mapToGL(event->pos().x(), event->pos().y());
        Point2D lastGL = mapToGL(lastMousePos.x(), lastMousePos.y());
        
        float dx = currentGL.x - lastGL.x;
        float dy = currentGL.y - lastGL.y;
        
        TranslateShape(currentShape, dx, dy);
        
        lastMousePos = event->pos();
        update(); 
    }
}

void glWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        isScaling = false;
        selectedVertexIndex = -1;
    } else if (event->button() == Qt::RightButton) {
        isRotating = false;
    }
}
