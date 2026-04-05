# 🎯 2D to 3D Shape Transformer (Qt + OpenGL)

A modern **C++ application built using Qt and OpenGL** that enables users to interactively draw 2D geometric shapes and transform them into dynamic 3D objects with real-time manipulation.

---

## 🚀 Features

### 🧩 Interactive 2D Shape Creation
- Create basic primitives:
  - Triangle  
  - Square  
  - Rectangle  
  - Circle  

### 🎯 Precision Transformations
- **Translation**  
  Drag the shape from its center to move it smoothly.

- **Scaling (Vertex Anchoring)**  
  Drag any vertex while the opposite vertex remains fixed, ensuring proportional scaling.

### 🔄 2D → 3D Conversion
- Convert 2D shapes into **3D extruded models** instantly.

- **3D Rotation**
  - Right-click + drag to rotate along X and Y axes  
  - Smooth real-time interaction

---

## 📸 Output Preview

### 🔺 Triangle (2D)
![Triangle](img/triangle_2d.png)

### 🔺 Triangle (3D)
![Triangle 3D](img/triangle_3d.png)

### 🔷 Square (2D)
![Square](img/square_2d.png)

### 🔶 Rectangle (2D)
![Rectangle](img/rectangle_2d.png)

### 🧊 Cube (3D Output)
![Cube](img/cube.png)

### 🔵 Circle (2D)
![Circle](img/circle.png)

### 🔵 Cylinder (3D Output)
![Cylinder](img/cylinder.png)

---

## 🛠️ Tech Stack

- **Language**: C++ (C++17)
- **Framework**: Qt (Widgets + OpenGL)
- **Graphics**: OpenGL
- **UI**: QWidget-based interface

---

## ⚙️ Setup & Installation

### 🔹 Clone Repository
```bash
git clone https://github.com/OceanicCoder09/QtGLShapes.git
cd QtGLShapes
🔹 Option 1: Qt Creator (Recommended ✅)
Open Qt Creator

Open file:

2DShapesTransform.pro
Configure kit (Qt 6)
Build & Run
🔹 Option 2: Visual Studio

Requires Qt Visual Studio Tools installed

Open:

2DShapesTransform.vcxproj

Set configuration:

Debug | x64
Build → Run
🎮 How to Use
Select a shape from dropdown
Left-click to create shape
Drag center → move shape
Drag vertex → scale shape
Click Convert to 3D
Right-click + drag → rotate
📁 Project Structure
├── img/            # Screenshots
├── shapes/         # Shape implementations
├── operations/     # Transform logic
├── ui/             # UI components
├── main.cpp        # Entry point
├── 2DShapesTransform.pro
💡 Key Concepts Used
Vertex manipulation
Mesh generation (2D → 3D extrusion)
Transformation matrices
OpenGL rendering pipeline
👨‍💻 Author

OceanicCoder09
