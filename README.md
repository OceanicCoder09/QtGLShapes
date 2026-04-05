# 🎯 2D to 3D Shape Transformer

A modern C++ Qt and OpenGL application that allows users to interactively draw, transform, and convert 2D geometric shapes into fully operational 3D objects.

---

## 📸 Application Preview

![App Preview](img/Screenshot%202026-04-05%20123545.png)

---

## 🚀 Overview & Features

* **Interactive 2D Shapes**: Generate primitives including Triangles, Squares, Rectangles, and Circles.

* **Precision Object Controls**:

  * **Translate**: Left-click and drag near the center of any shape to fluidly move it.
  * **Scale via Vertex Anchoring**: Left-click and drag a specific shape corner. The application anchors the opposite vertex, uniformly scaling the object while preserving geometry.

* **2D to 3D Conversion**:

  * Instantly transform your flat polygon into a 3D extrusion.
  * **Dynamic 3D Rotation**: Right-click and drag to rotate across X and Y axes.

---

## 📸 Output Screens

### 🔺 Triangle (2D)

![Triangle](img/Screenshot%202026-04-05%20123545.png)

### 🔺 Triangle (3D)

![Triangle 3D](img/Screenshot%202026-04-05%20123642.png)

### 🔷 Square

![Square](img/Screenshot%202026-04-05%20123720.png)

### 🔶 Rectangle

![Rectangle](img/Screenshot%202026-04-05%20123751.png)

### 🧊 Cube (3D Output)

![Cube](img/Screenshot%202026-04-05%20123826.png)

### 🔵 Circle (2D)

![Circle](img/Screenshot%202026-04-05%20124152.png)

### 🔵 Circle (3D Extrusion)

![Circle 3D](img/Screenshot%202026-04-05%20124222.png)

---

## 🛠️ Build Requirements

* CMake (3.16+)
* Qt 6 (Core, GUI, Widgets, OpenGLWidgets)
* C++17 compatible compiler

---

## ⚙️ Setup & Installation

```bash
git clone https://github.com/OceanicCoder09/QtGLShapes.git
```

1. Open in Visual Studio / Qt Creator
2. Configure CMake (Qt6 path required)
3. Build and run

---

## 🎮 Usage Guide

1. Select shape from dropdown
2. Left-click to create
3. Drag center → move
4. Drag vertex → scale
5. Click **Convert to 3D**
6. Right-click + drag → rotate

---

## 👨‍💻 Author

OceanicCoder09

---
