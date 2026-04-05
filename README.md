# 🎯 2D to 3D Shape Transformer - FreeCAD

A modern C++ Qt and OpenGL application that allows users to interactively draw, transform, and convert 2D geometric shapes into fully operational 3D objects.

---

## 🚀 Overview & Features

* **Interactive 2D Shapes**: Generate primitives including Triangles, Squares, Rectangles, and Circles.

* **Precision Object Controls**:
  * **Translate**: Left-click and drag near the center of any shape to fluidly move it.
  * **Scale via Vertex Anchoring**: Left-click and drag a specific shape corner. The application anchors the opposite vertex, uniformly scaling the object while preserving geometry.

* **2D to 3D Conversion**:
  * Instantly transform your flat polygon into a 3D extrusion.

* **Dynamic 3D Rotation**:
  * Right-click and drag to rotate across X and Y axes.

---

## 📸 Output Screens

### 🔺 Triangle (2D)
![Triangle](img/triangle_2d.png)

### 🔺 Triangle (3D)
![Triangle 3D](img/triangle_3d.png)

### 🔷 Square
![Square](img/square_2d.png)

### 🔶 Rectangle
![Rectangle](img/rectangle_2d.png)

### 🧊 Cube (3D Output)
![Cube](img/cube.png)

### 🔵 Circle (2D)
![Circle](img/circle.png)

### 🔵 Cylinder (3D Extrusion)
![Cylinder](img/cylinder.png)

---

## 🛠️ Build Requirements

* Qt 6 (Core, GUI, Widgets, OpenGLWidgets)
* Qt Creator (recommended) or Visual Studio with Qt support
* C++17 compatible compiler

---

## ⚙️ Setup & Installation

```bash
git clone https://github.com/OceanicCoder09/QtGLShapes.git

### Using Qt Creator (.pro file)

1. Open **Qt Creator**
2. Click **Open Project**
3. Select `2DShapesTransform.pro`
4. Configure kit (Qt 6)
5. Click **Build & Run**

---

### Using Visual Studio (Qt Extension)

1. Open Visual Studio
2. Install **Qt VS Tools**
3. Open `.pro` file or convert to VS project
4. Build and run

---

## 🎮 Usage Guide

1. Select shape from dropdown  
2. Left-click to create  
3. Drag center → move  
4. Drag vertex → scale  
5. Click **Convert to 3D**  
6. Right-click + drag → rotate  

