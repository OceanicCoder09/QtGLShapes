# 2D Shapes Transformation Tool
## Project Overview
This project is a C++ desktop application built using the Qt6 framework and the OpenGL graphics library. The application demonstrates core computer graphics fundamentals—specifically, manipulating pure mathematical representations of 2D shapes (Triangles, Squares, and Rectangles) without relying on high-level matrix stacks or automated bounding-box functions provided by typical UI suites. 

All primary manipulation and geometric features (Translation, Scaling by vertex drag, and Rotation) are correctly formulated by calculating matrices directly upon the vector vertices inside the CPU logic before forwarding the absolute mapped coordinates onto the OpenGL renderer (`glBegin`, `glEnd`).

## Data Flow & Execution Pipeline
1. **Entry Point (`main.cpp`)**: The application kicks off by creating the `QApplication` instance and presenting `MainWindow`.
2. **UI Container (`MainWindow`)**: Houses user interface controls (Start/Clear buttons and the Shape Selection dropdown). It integrates the custom `GLWidget` onto the main stage. 
3. **Graphics Canvas (`GLWidget`)**: Manages the OpenGL context. It intercepts your mouse clicks, maps system window pixels into normalized OpenGL values (-1.0 to +1.0 coordinate plane), and routes those pure mathematical inputs down to the active Shape.
4. **Hardware Rendering (`Shape::draw()`)**: Upon receiving `update()` commands, the OpenGL rendering thread locks the active vertex list, draws the filled body inside a `GL_POLYGON`, outlines it with `GL_LINE_LOOP`, and marks valid interactive hit-points via `GL_POINTS`.

---

## File Breakdown & Responsibilities

### `CMakeLists.txt`
The primary build-system descriptor file. It configures the C++17 standard bindings, enforces Qt's special parsing requirements (MOC processing for `QObjects` like `MainWindow`), successfully links libraries against `Qt6::OpenGLWidgets`, and guarantees that dynamically mapped DLL links automatically clone themselves via `windeployqt` upon successful build execution so that the app doesn't unexpectedly crash on launch.

### `main.cpp`
The absolute minimum entry point for a standard Qt C++ platform. It hooks directly into the core executable cycle and starts the Qt Event handler loop block.

### `MainWindow.h` & `MainWindow.cpp`
**The User Interface wrapper.** 
- Serves as the overarching Qt Window hosting basic graphical wrappers like `QPushButton`, `QComboBox` for shape choices, and horizontal box layouts. 
- Dispatches UI Signal triggers (e.g. clicking the "Create" button) directly down into its internal `GLWidget` logic.

### `GLWidget.h` & `GLWidget.cpp`
**The Interactive Hardware Viewport.** 
- Inherits from `QOpenGLWidget` and specifically forces legacy graphics compatibility configurations. 
- Overrides primary UI interactions (`mousePressEvent`, `mouseMoveEvent`, `keyPressEvent`). 
- **The Core Mapping Logic:** Implements `mapToGL()` matching pixel data `(0, Width)` precisely into Device Normalized OpenGL blocks bounds ranging strictly from `(-1.0, 1.0)`, ensuring precision geometry clicks universally.
- Handles determining whether user-inputs fall into an `isScaling` mode (vertex pulled) or an `isDragging` mode (shape-body pulled).

### `Shape.h` & `Shape.cpp`
**The pure mathematical structure abstraction system.** 
The most important backend folder consisting of the base template class and children shapes (`Triangle`, `Square`, `RectangleShape`).
- Contains the `Point2D` float arrays defining local space definitions.
- `contains()`: Casts rigorous "Ray-casting" logic formulas perfectly discerning if complex float mouse inputs mathematically fall within the exact geometry space inside of its boundary walls to authorize translation dragging.
- `getVertexIndexAt()`: A Pythagorean distance logic boundary check designed explicitly for precise vertex highlighting to activate drag-based scaling mode. 
- `scaleByDrag()` / `translate()` / `rotate()`: Matrix functions updating linear geometric calculations locally against vertices relative to the determined structure centroid logic. 
- Relies on safely abstracted `QOpenGLVersionFunctionsFactory` calls guaranteeing that low-level hardware drivers seamlessly fetch OpenGL 1.1 contexts to output rendering cleanly on Windows.
