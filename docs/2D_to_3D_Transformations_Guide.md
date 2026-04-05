# 2D to 3D Conversion & Transformations Guide

This guide breaks down exactly how flat 2D shapes are extruded into 3D objects, and how we built simple math functions to move, scale, and rotate them using beginner-friendly C++.

---

## 1. How We Converted 2D to 3D
Instead of relying on complex 3D modeling libraries or automated engines, we extruded our 2D shapes into 3D manually using standard layered rendering logic.

### The Strategy (Extrusion)
Every 2D shape is essentially a flat list of `(X, Y)` coordinate points on a piece of paper. To make it a true 3D block, we:
1. Act as if the flat 2D shape exists exactly in the dead center of the screen (Z = 0).
2. Pushed a "Front Face" slightly towards the camera by giving it a positive depth value (`zFront`).
3. Pushed a "Back Face" slightly away from the camera by giving it a negative depth value (`zBack`).
4. Connected the matching corners of the Front Face and the Back Face to build the "Sides" (Walls).

### Handled in `ShapeRenderer.cpp`
When a shape is upgraded from 2D to 3D via `shape->set3D(true)`, the `ShapeRenderer` breaks the drawing into four easy steps:
- **`draw3DFrontFace()`**: Draws a solid white polygon connecting the `(X, Y, zFront)` points.
- **`draw3DBackFace()`**: Draws a darker gray polygon connecting the `(X, Y, zBack)` points.
- **`draw3DSides()`**: Loops through every corner. It draws a 4-point rectangle (a `GL_QUADS`) connecting:
  `Corner 1 Front` -> `Corner 2 Front` -> `Corner 2 Back` -> `Corner 1 Back`. 
  It uses simple `if-else` color blocks to paint each wall so you can easily distinguish depth.
- **`draw3DEdges()`**: Connects white lines over the edges of the walls to fake standard lighting and give visual depth so you can clearly see the geometry's footprint.

---

## 2. Performing Transformation Features
Transformations apply directly to the exact geometric coordinates (`X` and `Y`) of the shape, altering its mathematical footprint directly. This keeps the code simple and easy to track!

### Translation (Moving)
**Goal:** Shift the entire shape uniformly.
**How it fits together in code:** To move a shape, we simply add the distance the mouse moved to every single vertex in the shape.
1. `GLWidget` tracks the mouse moving, generating a distance offset (`dx` and `dy`).
2. The `Translate` function loops through the shape's `points`.
3. `points[i].x = points[i].x + dx;`
4. `points[i].y = points[i].y + dy;`

### Scaling (Resizing)
**Goal:** Expand or shrink the shape based on dragging away from (or towards) its center.
**How it fits together in code:** To scale a shape, we calculate how far a corner is from the *Center Point* of the shape, and multiply that distance by our `factor`.
1. `GLWidget` triggers moving the mouse when in Scaling Mode.
2. The `Scale` function isolates the exact center of the shape (`sumX / size`).
3. It calculates the corner's original distance `dist_x` from the center.
4. It multiplies that distance by the `scaleFactor`.
5. It adds the multiplied distance back to the center point to get the new, pushed-out coordinate.  
*(For 3D shapes, we also simply multiply the `depth` thickness variable by the `scaleFactor` so it grows proportionately thicker in 3D dimensions!)*.


