QT += core gui widgets openglwidgets opengl
CONFIG += c++17

TARGET = 2DShapesTransform
TEMPLATE = app

INCLUDEPATH += $$PWD/ui $$PWD/shapes $$PWD/operations

SOURCES += \
    main.cpp \
    ui/MainWindow.cpp \
    ui/glWindow.cpp \
    shapes/Shape.cpp \
    shapes/ShapeRenderer.cpp \
    shapes/Triangle.cpp \
    shapes/Square.cpp \
    shapes/RectangleShape.cpp \
    shapes/Circle.cpp \
    operations/Transformations.cpp

HEADERS += \
    ui/MainWindow.h \
    ui/glWindow.h \
    shapes/Shape.h \
    shapes/ShapeRenderer.h \
    shapes/Triangle.h \
    shapes/Square.h \
    shapes/RectangleShape.h \
    shapes/Circle.h \
    operations/Transformations.h
