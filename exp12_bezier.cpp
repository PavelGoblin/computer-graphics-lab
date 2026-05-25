// ===================================================================
// Experiment 12: Bezier Curve (Cubic)
//
// THEORY:
// A Bezier curve is defined by CONTROL POINTS. The curve passes
// through the FIRST and LAST points but only approaches the middle ones.
//
// CUBIC BEZIER (4 control points: P₀, P₁, P₂, P₃):
//
// B(t) = (1-t)³·P₀ + 3t(1-t)²·P₁ + 3t²(1-t)·P₂ + t³·P₃
//
// Where t goes from 0 to 1:
//   t = 0 → curve starts at P₀
//   t = 1 → curve ends at P₃
//
// BERNSTEIN BASIS POLYNOMIALS (weights for each point):
//   B₀(t) = (1-t)³      ← weight for P₀
//   B₁(t) = 3t(1-t)²    ← weight for P₁
//   B₂(t) = 3t²(1-t)    ← weight for P₂
//   B₃(t) = t³           ← weight for P₃
//
// PROPERTIES:
// - Curve lies inside the CONVEX HULL of control points
// - Passes through P₀ at t=0 and P₃ at t=1
// - Tangent at start = direction P₀→P₁
// - Tangent at end   = direction P₂→P₃
// - Moving one control point affects the ENTIRE curve (global control)
//
// DE CASTELJAU'S ALGORITHM (alternative method):
// Recursive linear interpolation:
//   1. Connect control points with lines
//   2. Split each line at parameter t
//   3. Connect the split points → repeat until 1 point remains
// ===================================================================

#include <graphics.h>
#include <cmath>
#include <conio.h>

// Function: Draw a cubic Bezier curve from 4 control points
// x[4], y[4] = control point coordinates
// steps = how many points to calculate (more = smoother)
void bezierCurve(int x[4], int y[4], int steps = 100) {
    // Evaluate the curve at "steps" equally-spaced t values
    for (int i = 0; i <= steps; i++) {
        // t goes from 0.0 to 1.0
        float t = (float)i / steps;
        float u = 1 - t;    // u = (1-t), just a convenience

        // Bernstein basis polynomials (cubic degree, n=3)
        float b0 = u * u * u;               // (1-t)³  — weight for P₀
        float b1 = 3 * t * u * u;           // 3t(1-t)² — weight for P₁
        float b2 = 3 * t * t * u;           // 3t²(1-t) — weight for P₂
        float b3 = t * t * t;               // t³ — weight for P₃

        // Weighted sum of all control points
        // This is the core Bezier formula: B(t) = Σ Pᵢ · Bᵢ(t)
        int px = (int)(b0 * x[0] + b1 * x[1] + b2 * x[2] + b3 * x[3] + 0.5f);
        int py = (int)(b0 * y[0] + b1 * y[1] + b2 * y[2] + b3 * y[3] + 0.5f);

        // Plot this point on the curve
        putpixel(px, py, YELLOW);
    }
}

// Function: Draw the control polygon (lines connecting control points)
// Also highlights each control point with a red dot
void drawControlPolygon(int x[4], int y[4]) {
    // Draw the CONTROL POLYGON (white lines connecting points)
    setcolor(WHITE);
    for (int i = 0; i < 3; i++) {
        line(x[i], y[i], x[i+1], y[i+1]);
    }

    // Draw CONTROL POINTS (red filled circles)
    setcolor(RED);
    for (int i = 0; i < 4; i++) {
        circle(x[i], y[i], 4);          // Circle outline
        setfillstyle(SOLID_FILL, RED);
        floodfill(x[i], y[i], RED);     // Fill it
    }

    // Label each control point
    setcolor(WHITE);
    outtextxy(x[0], y[0] - 15, "P0");   // Start point
    outtextxy(x[1], y[1] - 15, "P1");   // Control point 1
    outtextxy(x[2], y[2] - 15, "P2");   // Control point 2
    outtextxy(x[3], y[3] - 15, "P3");   // End point
}

// ===================================================================
// MAIN FUNCTION
// ===================================================================
int main() {
    initwindow(640, 480, "Bezier Curve");

    // ================================================================
    // CURVE 1: A simple "S" shape
    // P₀ = (100, 300) — start at bottom-left
    // P₁ = (200, 100) — pulls curve up
    // P₂ = (300, 100) — continues upward pull
    // P₃ = (400, 300) — ends at bottom-right
    // ================================================================
    int x1[4] = {100, 200, 300, 400};
    int y1[4] = {300, 100, 100, 300};

    drawControlPolygon(x1, y1);   // Draw white lines + red dots
    bezierCurve(x1, y1);          // Draw the actual yellow curve
    outtextxy(10, 10, "Bezier Curve 1");

    // ================================================================
    // CURVE 2: A different shape
    // ================================================================
    int x2[4] = {100, 250, 350, 500};
    int y2[4] = {400, 250, 350, 400};

    drawControlPolygon(x2, y2);
    bezierCurve(x2, y2);
    outtextxy(10, 390, "Bezier Curve 2");

    // Legend
    outtextxy(10, 420, "White = Control polygon | Red = Control points | Yellow = Bezier curve");

    getch();
    closegraph();
    return 0;
}
