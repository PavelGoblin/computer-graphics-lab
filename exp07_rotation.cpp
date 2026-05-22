// ===================================================================
// Experiment 07: 2D Rotation of a Line and Triangle
//
// THEORY:
// Rotation turns an object around a fixed point (called the pivot).
// By convention, positive angle = counterclockwise rotation.
//
// FORMULA (rotation about origin by angle θ):
//   x' = x·cos(θ) - y·sin(θ)
//   y' = x·sin(θ) + y·cos(θ)
//
// MATRIX FORM:
//   | x' |   | cosθ  -sinθ  0 |   | x |
//   | y' | = | sinθ   cosθ  0 | * | y |
//   | 1  |   |  0      0    1 |   | 1 |
//
// ROTATION ABOUT ARBITRARY POINT (cx, cy):
// We can't just rotate around any point with the simple formula.
// We need 3 steps:
//   1. TRANSLATE so the pivot goes to origin:  T(-cx, -cy)
//   2. ROTATE about origin:                    R(θ)
//   3. TRANSLATE back:                         T(cx, cy)
//
// Combined:  P' = T(cx, cy) · R(θ) · T(-cx, -cy) · P
//
// In code:  x_rel = x - cx,  y_rel = y - cy
//           x_new = cx + x_rel·cosθ - y_rel·sinθ
//           y_new = cy + x_rel·sinθ + y_rel·cosθ
// ===================================================================

#include <graphics.h>
#include <cmath>         // For cos(), sin()
#include <conio.h>
#include <cstdio>

#define PI 3.14159265    // π for converting degrees to radians

// Helper: Draw a triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

// Helper: Draw a line
void drawLine(int x1, int y1, int x2, int y2, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
}

// Function: Rotate a point (x,y) about pivot (cx,cy) by angle degrees
// Result is stored in (xOut, yOut)
void rotatePoint(int x, int y, int cx, int cy, float angle, int &xOut, int &yOut) {
    // Step 1: Convert angle from degrees to radians
    float rad = angle * PI / 180.0;
    float cosA = cos(rad);
    float sinA = sin(rad);

    // Step 2: Translate point relative to pivot
    // (xRel, yRel) = position relative to rotation center
    int xRel = x - cx;
    int yRel = y - cy;

    // Step 3: Apply rotation formula about origin
    // x_new = x·cosθ - y·sinθ
    // y_new = x·sinθ + y·cosθ
    int xRot = (int)(xRel * cosA - yRel * sinA + 0.5f);
    int yRot = (int)(xRel * sinA + yRel * cosA + 0.5f);

    // Step 4: Translate back to original position
    xOut = cx + xRot;
    yOut = cy + yRot;
}

// ===================================================================
// MAIN FUNCTION
// ===================================================================
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // ================================================================
    // PART 1: Rotate a LINE about its start point
    // ================================================================
    int lx1 = 100, ly1 = 300;   // Pivot point (start of line)
    int lx2 = 250, ly2 = 300;   // End of line

    // Original line (horizontal, to the right)
    drawLine(lx1, ly1, lx2, ly2, WHITE);
    outtextxy(lx1, ly1 + 10, "Original");

    // Rotate by 45 degrees
    int rx, ry;
    rotatePoint(lx2, ly2, lx1, ly1, 45, rx, ry);
    drawLine(lx1, ly1, rx, ry, YELLOW);
    outtextxy(rx + 5, ry, "Rotated 45 deg");

    // Rotate by 90 degrees
    rotatePoint(lx2, ly2, lx1, ly1, 90, rx, ry);
    drawLine(lx1, ly1, rx, ry, GREEN);
    outtextxy(rx + 5, ry, "Rotated 90 deg");

    // ================================================================
    // PART 2: Rotate a TRIANGLE about its centroid
    // ================================================================
    // Triangle vertices
    int x1 = 400, y1 = 80;      // Top
    int x2 = 500, y2 = 200;     // Right
    int x3 = 300, y3 = 200;     // Left

    // Centroid = average of all vertices
    // This is the "center of mass" of the triangle
    int cx = (x1 + x2 + x3) / 3;
    int cy = (y1 + y2 + y3) / 3;

    // Original triangle
    drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
    outtextxy(cx - 30, cy, "Original");

    // Rotated by 60 degrees
    int rx1, ry1, rx2, ry2, rx3, ry3;
    rotatePoint(x1, y1, cx, cy, 60, rx1, ry1);
    rotatePoint(x2, y2, cx, cy, 60, rx2, ry2);
    rotatePoint(x3, y3, cx, cy, 60, rx3, ry3);
    drawTriangle(rx1, ry1, rx2, ry2, rx3, ry3, MAGENTA);
    outtextxy(cx - 30, cy + 80, "Rotated 60 deg");

    // Rotated by 120 degrees
    rotatePoint(x1, y1, cx, cy, 120, rx1, ry1);
    rotatePoint(x2, y2, cx, cy, 120, rx2, ry2);
    rotatePoint(x3, y3, cx, cy, 120, rx3, ry3);
    drawTriangle(rx1, ry1, rx2, ry2, rx3, ry3, CYAN);
    outtextxy(cx - 30, cy + 160, "Rotated 120 deg");

    outtextxy(10, 10, "Experiment 07: 2D Rotation");
    outtextxy(10, 30, "Rotation about line-start / triangle-centroid");

    getch();
    closegraph();
    return 0;
}
