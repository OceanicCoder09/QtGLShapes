# QtGLShapes Architecture Documentation

This document provides a detailed breakdown of the file structure and the roles of each file in the QtGLShapes application. The project is explicitly designed with a beginner-friendly object-oriented approach—separating user interface, geometric data, drawing logic, and mathematical operations.

---

### 1. The Entry Point
- **`main.cpp`**  
  The launchpad of the application. It simply initializes the Qt application environment, creates the main application window, and starts the infinite UI event loop.

### 2. User Interface (`ui/` folder)
- **`ui/MainWindow.h` & `ui/MainWindow.cpp`**  
  Controls the primary application window layout. This includes setting up the toolbars, adding the interactive buttons (like "Draw Triangle", "Convert to 3D", "Scale"), and dropping the OpenGL drawing canvas (`GLWidget`) exactly in the center of the screen.
  
- **`ui/GLWidget.h` & `ui/GLWidget.cpp`**  
  The central brain for user interaction. This file manages the OpenGL context (the blank digital canvas) and heavily listens to your mouse clicks, mouse dragging, and keyboard input. When you drag your mouse to move or scale a shape, `GLWidget` intercepts those clicks, figures out what state you are in, and dynamically triggers the mathematical transformation operations.

### 3. Geometric Shapes (`shapes/` folder)
The geometry logic is structured using class inheritance (a core C++ concept) to share common variables like `vertices` (list of points) and `is3D` toggles without copy-pasting code.

- **`shapes/Shape.h` & `shapes/Shape.cpp`**  
  The foundational blueprint for all shapes. It stores the exact `X` and `Y` coordinates of the shape's corners (vertices) inside a C++ `std::vector`, determines if it is currently set to 2D or 3D, and holds the shape's `depth` (thickness).
  
- **`shapes/Triangle.cpp`, `Square.cpp`, `RectangleShape.cpp`**  
  These are "child" classes that inherit from `Shape`. Their only job is to populate their lists of `vertices` with the specific flat 2D corners necessary to form their respective geometries when they are initially drawn onto the screen.
  
- **`shapes/ShapeRenderer.h` & `ShapeRenderer.cpp`**  
  The Graphics Engine. Completely isolated from the raw shape mathematics, this file takes any geometric shape handed to it and converts its coordinates into low-level OpenGL rendering commands (`glVertex3f`). Because of this file, `Shape.cpp` doesn't need to bloat itself with rendering routines. It explicitly houses custom, step-by-step logic to draw the front, back, sides, and edges of 3D objects using explicit variables like `currentX` and `nextY`.

### 4. Mathematical Operations (`operations/` folder)
- **`operations/Transformations.h` & `Transformations.cpp`**  
  Contains the raw, beginner-friendly mathematical formulas universally used to mutate the shape footprint. Instead of embedding complex math inside the mouse clicks of `GLWidget`, the application passes coordinate data to these simple standalone functions to execute Translations (moving) and Scaling (resizing).
