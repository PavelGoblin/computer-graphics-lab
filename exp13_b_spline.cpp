// ===================================================================
// Experiment 13: B-Spline Curve (Uniform Cubic B-Spline)
//
// THEORY:
// B-Spline = "Basis Spline". Unlike Bezier (where all points affect
// the whole curve), B-Spline gives LOCAL CONTROL — each control point
// only affects a SMALL region of the curve.
//
// KEY DIFFERENCES FROM BEZIER:
//   - Bezier: n+1 control points → degree n (global control)
//   - B-Spline: n+1 control points, degree k (local control)
//   - Bezier passes through endpoints; B-Spline generally doesn't
//   - B-Spline: C² continuous (smoother joins)
//
// UNIFORM CUBIC B-SPLINE:
// Each segment uses 4 control points (Pᵢ, Pᵢ₊₁, Pᵢ₊₂, Pᵢ₊₃):
//
//   Bᵢ(t) = (1/6) × [
//       (1-t)³·Pᵢ +
//       (3t³ - 6t² + 4)·Pᵢ₊₁ +
//       (-3t³ + 3t² + 3t + 1)·Pᵢ₊₂ +
//       t³·Pᵢ₊₃
//   ]
//
// MATRIX FORM:
//   Bᵢ(t) = [t³ t² t 1] · (1/6) · M · [Pᵢ Pᵢ₊₁ Pᵢ₊₂ Pᵢ₊₃]ᵀ
//
//       [-1  3 -3  1]
//   M = [ 3 -6  3  0]
//       [-3  0  3  0]
//       [ 1  4  1  0]
//
// PROPERTIES:
// - Changing Pᵢ affects at most 4 segments (local!)
// - C² continuous (2nd derivative matches at joins)
// - Does NOT pass through control points (smooth approximation)
// ===================================================================

#include <graphics.h>
#include <cmath>
#include <conio.h>
#include <cstdio>

#define NUM_POINTS 6   // Number of control points

// Function: Draw a uniform cubic B-Spline through control points
// controlX[], controlY[] = control point coordinates
// n = number of control points
// steps = resolution per segment
void bSpline(int controlX[], int controlY[], int n, int steps = 50) {
    // ---- Draw CONTROL POINTS (red filled circles) ----
    setcolor(RED);
    for (int i = 0; i < n; i++) {
        circle(controlX[i], controlY[i], 4);
        setfillstyle(SOLID_FILL, RED);
        floodfill(controlX[i], controlY[i], RED);
    }

    // ---- Draw CONTROL POLYGON (white lines) ----
    setcolor(WHITE);
    for (int i = 0; i < n - 1; i++) {
        line(controlX[i], controlY[i], controlX[i+1], controlY[i+1]);
    }

    // ---- Draw the B-SPLINE CURVE (yellow) ----
    setcolor(YELLOW);

    // For uniform cubic B-spline, each segment needs 4 control points
    // Segment i uses: Pᵢ, Pᵢ₊₁, Pᵢ₊₂, Pᵢ₊₃
    // With n points, we get (n - 3) segments
    for (int i = 0; i < n - 3; i++) {
        for (int j = 0; j <= steps; j++) {
            float t = (float)j / steps;   // t from 0 to 1
            float t2 = t * t;
            float t3 = t2 * t;

            // Uniform cubic B-spline basis functions
            // These come from the B-spline basis matrix divided by 6
            float b0 = (1.0f/6.0f) * (-t3 + 3*t2 - 3*t + 1);   // Weight for Pᵢ
            float b1 = (1.0f/6.0f) * ( 3*t3 - 6*t2 + 4);        // Weight for Pᵢ₊₁
            float b2 = (1.0f/6.0f) * (-3*t3 + 3*t2 + 3*t + 1);  // Weight for Pᵢ₊₂
            float b3 = (1.0f/6.0f) * t3;                         // Weight for Pᵢ₊₃

            // Weighted sum of the 4 control points for this segment
            int px = (int)(b0 * controlX[i]   + b1 * controlX[i+1]
                         + b2 * controlX[i+2] + b3 * controlX[i+3] + 0.5f);
            int py = (int)(b0 * controlY[i]   + b1 * controlY[i+1]
                         + b2 * controlY[i+2] + b3 * controlY[i+3] + 0.5f);

            putpixel(px, py, YELLOW);   // Plot the curve point
        }
    }
}

// ===================================================================
// MAIN FUNCTION
// ===================================================================
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Define 6 control points for the B-Spline
    int x[NUM_POINTS] = {100, 180, 280, 380, 480, 560};
    int y[NUM_POINTS] = {200,  80, 300,  80, 300, 200};

    // Draw the curve
    bSpline(x, y, NUM_POINTS);

    // Label each control point
    setcolor(WHITE);
    for (int i = 0; i < NUM_POINTS; i++) {
        char label[5];
        sprintf(label, "P%d", i);
        outtextxy(x[i] + 5, y[i] + 5, label);
    }

    // Legend
    outtextxy(10, 10, "Experiment 13: B-Spline Curve (Uniform Cubic)");
    outtextxy(10, 30, "White = Control polygon | Red = Control points | Yellow = Curve");
    outtextxy(10, 50, "Note: Smooth C2 continuous curve (does NOT pass through endpoints)");

    getch();
    closegraph();
    return 0;
}
