cmake_minimum_required(VERSION 3.16)
project(2DShapesTransform VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets OpenGL)

add_executable(2DShapesTransform
    main.cpp
    ui/MainWindow.cpp
    ui/MainWindow.h
    ui/GLWidget.cpp
    ui/GLWidget.h
    shapes/Shape.cpp
    shapes/Shape.h
    shapes/ShapeRenderer.cpp
    shapes/ShapeRenderer.h
    shapes/Triangle.cpp
    shapes/Triangle.h
    shapes/Square.cpp
    shapes/Square.h
    shapes/RectangleShape.cpp
    shapes/RectangleShape.h
    shapes/Circle.cpp
    shapes/Circle.h
    operations/Transformations.cpp
    operations/Transformations.h
)

target_include_directories(2DShapesTransform PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/ui"
    "${CMAKE_CURRENT_SOURCE_DIR}/shapes"
    "${CMAKE_CURRENT_SOURCE_DIR}/operations"
)

target_link_libraries(2DShapesTransform PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
    Qt6::OpenGL
)

# Automate copying the required Qt DLLs (like Qt6OpenGLWidgetsd.dll) to the build output directory
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${Qt6_DIR}/../../../bin")
if(WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET 2DShapesTransform POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:2DShapesTransform>"
        COMMENT "Running windeployqt to automatically copy required Qt DLLs to the output directory..."
    )
endif()
