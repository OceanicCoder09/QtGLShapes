# Shapes Folder Explanation

This document acts as a tour guide for everything inside the `shapes/` directory. It explains precisely what each individual `.cpp` (code) and `.h` (header) file is responsible for and how they all connect together to establish geometry on the screen!

---

### 1. The Foundation
**`Shape.h` & `Shape.cpp`**
- **What it does:** This is the highest level "Parent Class" or "Blueprint" for all geometry. It exists to make sure every shape in the app operates consistently. 
- **The Header (`Shape.h`):** Defines the universal variables that every shape will need to exist: an array list to hold the corner coordinates (`vertices`), a boolean toggle checking if it is 2D or 3D (`is3D`), and a thickness magnitude (`depth`). It explicitly declares utility functions like `getCenter()` and `contains()` (for mouse clicks).
- **The Code (`Shape.cpp`):** Contains the actual math executing those utility functions. For example, it calculates the physical center of any given shape by averaging all X and Y coordinates. Crucially, it tells the shape to call upon `ShapeRenderer` whenever someone requests the shape be drawn onto the screen.

---

### 2. The Graphics Engine
**`ShapeRenderer.h` & `ShapeRenderer.cpp`**
- **What it does:** This is your isolated graphics pipeline. It acts entirely independently of the shape's coordinates to keep the `Shape.cpp` file clean. 
- **The Header (`ShapeRenderer.h`):** Declares a static engine containing specific broken-down rendering methods like `draw2D`, `draw3DFrontFace`, and `draw3DSides`.
- **The Code (`ShapeRenderer.cpp`):** This heavily commented powerhouse takes a shape's raw `vertices` data and physically plots them onto the OpenGL digital canvas window using `glVertex3f`. This file determines the manual color paint logic to emulate lighting shadows, explicitly connecting corners together to visually fake 3D extrusion footprints in the `draw3DSides` method.

---

### 3. The Geometries
Because you built this application using Object-Oriented Programming (OOP) inheritance, these "child" classes inherit everything from `Shape.h`. This means `Triangle`, `Square`, and `RectangleShape` instantly gain the ability to interact with the mouse, move around the screen, and jump into 3D without writing any unique logic!

**`Triangle.h` & `Triangle.cpp`**
- **What it does:** Represents a three-sided object. Upon creation, `Triangle.cpp` simply adds exactly 3 specific predefined `(X, Y)` coordinate points to its inherited `vertices` list.

**`Square.h` & `Square.cpp`**
- **What it does:** Represents a perfect four-sided box. When you press the Square button, `Square.cpp` initializes its geometry by adding 4 mathematically perfectly spaced (e.g., exactly +0.5 and -0.5) corner coordinates to its internal list, establishing an identical width and height.

**`RectangleShape.h` & `RectangleShape.cpp`**  
- **What it does:** Specifically acts as a stretched bounding box. Like the Square, it establishes 4 explicit corners, but uniquely pulls its left/right coordinates further apart (e.g., width = 1.6 vs height = 1.0) so it visually appears visually stretched compared to a standard square block.
