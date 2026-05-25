// ===================================================================
// Experiment 09: 3D Rotation About an Arbitrary Axis
//
// THEORY:
// Rotating a 3D object about ANY line in space (not just x, y, z).
// We use Rodrigues' Rotation Formula — the cleanest mathematical way.
//
// RODRIGUES' FORMULA:
// Given:
//   - v = point to rotate (as vector from origin)
//   - u = unit vector along the rotation axis
//   - θ = rotation angle
//
//   v' = v·cos(θ) + (u × v)·sin(θ) + u·(u·v)·(1 - cos(θ))
//
// Where:
//   u × v  = cross product of u and v
//   u · v  = dot product of u and v
//
// STEPS IN CODE:
// 1. Translate so axis passes through origin
// 2. Normalize the axis direction to get unit vector u
// 3. Apply Rodrigues' formula
// 4. Translate back
//
// VISUALIZATION:
// We use OBLIQUE PROJECTION to show 3D on a 2D screen:
//   screen_x = world_x + world_z * 0.5 * cos(30°)
//   screen_y = world_y + world_z * 0.5 * sin(30°)
// This gives a pseudo-3D appearance.
// ===================================================================

#include <graphics.h>
#include <cmath>
#include <conio.h>
#include <cstdio>

#define PI 3.14159265

// Structure to hold a 3D point
struct Point3D {
    int x, y, z;    // Coordinates in 3D space
};

// Function: Project a 3D point to 2D screen coordinates
// Uses oblique projection (simple pseudo-3D)
void project3D(Point3D p, int &sx, int &sy) {
    // Oblique projection formula:
    // The z coordinate is projected at 30° angle
    float angle = PI / 6;  // 30 degrees
    sx = p.x + (int)(p.z * 0.5 * cos(angle));
    sy = p.y + (int)(p.z * 0.5 * sin(angle));
}

// Function: Draw a cube given its 8 vertices
void drawCube(Point3D vertices[8], int color) {
    setcolor(color);

    // Define the 12 edges of a cube by vertex indices
    // Each pair [a,b] means an edge from vertex[a] to vertex[b]
    int edges[12][2] = {
        {0,1}, {1,2}, {2,3}, {3,0},   // Front face (4 edges)
        {4,5}, {5,6}, {6,7}, {7,4},   // Back face (4 edges)
        {0,4}, {1,5}, {2,6}, {3,7}    // Connecting edges (4 edges)
    };

    // Draw each edge by projecting both endpoints to 2D
    for (int i = 0; i < 12; i++) {
        int x1, y1, x2, y2;
        project3D(vertices[edges[i][0]], x1, y1);
        project3D(vertices[edges[i][1]], x2, y2);
        line(x1, y1, x2, y2);
    }
}

// Function: Rotate a point about arbitrary axis using Rodrigues' formula
// Parameters:
//   p = point to rotate (modified in place)
//   a1, a2 = two points defining the axis line
//   angle = rotation angle in degrees
void rotateAboutAxis(Point3D &p, Point3D a1, Point3D a2, float angle) {
    // === STEP 1: Translate so axis passes through origin ===
    // Subtract a1 from p (axis point → origin)
    float px = p.x - a1.x;
    float py = p.y - a1.y;
    float pz = p.z - a1.z;

    // === STEP 2: Get the axis direction vector ===
    float ax = a2.x - a1.x;    // Axis direction (not yet normalized)
    float ay = a2.y - a1.y;
    float az = a2.z - a1.z;

    // Normalize to get unit vector u
    float len = sqrt(ax*ax + ay*ay + az*az);
    float ux = ax / len;        // Unit vector components
    float uy = ay / len;
    float uz = az / len;

    // === STEP 3: Apply Rodrigues' Formula ===
    // v' = v·cosθ + (u×v)·sinθ + u·(u·v)·(1-cosθ)
    float rad = angle * PI / 180.0;
    float cosA = cos(rad);
    float sinA = sin(rad);

    // Compute u · v (dot product)
    float dot = px*ux + py*uy + pz*uz;

    // Compute u × v (cross product)
    float crossX = uy*pz - uz*py;
    float crossY = uz*px - ux*pz;
    float crossZ = ux*py - uy*px;

    // Apply the formula to each component
    float newX = px*cosA + crossX*sinA + ux*dot*(1 - cosA);
    float newY = py*cosA + crossY*sinA + uy*dot*(1 - cosA);
    float newZ = pz*cosA + crossZ*sinA + uz*dot*(1 - cosA);

    // === STEP 4: Translate back ===
    p.x = (int)(newX + a1.x + 0.5f);
    p.y = (int)(newY + a1.y + 0.5f);
    p.z = (int)(newZ + a1.z + 0.5f);
}

// ===================================================================
// MAIN FUNCTION
// ===================================================================
int main() {
    initwindow(640, 480, "3D Rotation About Arbitrary Axis");

    // Define a cube centered at (300, 200, 0)
    // Front face (z = -50), Back face (z = +50)
    Point3D cube[8] = {
        {250, 150, -50},   // 0: Front-top-left
        {350, 150, -50},   // 1: Front-top-right
        {350, 250, -50},   // 2: Front-bottom-right
        {250, 250, -50},   // 3: Front-bottom-left
        {250, 150,  50},   // 4: Back-top-left
        {350, 150,  50},   // 5: Back-top-right
        {350, 250,  50},   // 6: Back-bottom-right
        {250, 250,  50}    // 7: Back-bottom-left
    };

    // Draw original cube (WHITE)
    drawCube(cube, WHITE);
    outtextxy(10, 10, "Experiment 09: 3D Rotation About Arbitrary Axis");
    outtextxy(10, 30, "White = Original | Yellow = 45deg | Cyan = 90deg");

    // Define arbitrary axis: diagonal from front-top-left to back-bottom-right
    Point3D a1 = {260, 160, -40};   // Start of axis
    Point3D a2 = {340, 240,  40};   // End of axis

    // Rotate cube by 45 degrees and draw (YELLOW)
    Point3D rotated[8];
    for (int i = 0; i < 8; i++) {
        rotated[i] = cube[i];
        rotateAboutAxis(rotated[i], a1, a2, 45);
        rotated[i].y += 120;   // Shift down to separate from original
    }
    drawCube(rotated, YELLOW);

    // Rotate cube by 90 degrees and draw (CYAN)
    Point3D rotated2[8];
    for (int i = 0; i < 8; i++) {
        rotated2[i] = cube[i];
        rotateAboutAxis(rotated2[i], a1, a2, 90);
        rotated2[i].y += 240;  // Shift further down
    }
    drawCube(rotated2, CYAN);

    outtextxy(250, 420, "Rotation axis = cube body diagonal");

    getch();
    closegraph();
    return 0;
}
