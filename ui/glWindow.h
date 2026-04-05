#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "Shape.h"

class glWindow : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    explicit glWindow(QWidget *parent = nullptr);
    ~glWindow() override;

    void setPendingShapeType(int type); 
    void clearShape();
    void convertTo3D();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    int pendingShapeType;
    Shape* currentShape; 
    bool isDragging;
    bool isScaling;
    bool isRotating;
    int selectedVertexIndex;
    float xRot;
    float yRot;
    QPoint lastMousePos;
    
    Point2D mapToGL(int x, int y);
};

#endif
