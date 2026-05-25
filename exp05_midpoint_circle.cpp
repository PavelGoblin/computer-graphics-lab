// ===================================================================
// Experiment 05: Midpoint Circle Algorithm (Bresenham's Circle)
//
// THEORY:
// A circle with center (0,0) and radius r has equation:
//   f(x,y) = x² + y² - r² = 0
//
// Decision function:
//   f(x,y) < 0  → point is INSIDE the circle
//   f(x,y) = 0  → point is ON the circle
//   f(x,y) > 0  → point is OUTSIDE the circle
//
// 8-WAY SYMMETRY:
// If (x, y) is on the circle, these 8 points are also on it:
//   (±x, ±y), (±y, ±x)
// So we only compute 1/8th of the circle and reflect!
//
// DECISION PARAMETER:
//   p₀ = 1 - r             (starting at x=0, y=r)
//   At each step x → x+1:
//     if p < 0  → plot E   (x+1, y),   p += 2x + 3
//     if p ≥ 0  → plot SE  (x+1, y-1), p += 2(x-y) + 5
//
// The algorithm stops when x > y (we've covered 45 degrees)
// ===================================================================

#include <graphics.h>
#include <conio.h>

// Function: Plot 8 symmetric points of the circle
// Given one point (x,y) in the first octant, this plots all 8
// by reflecting across the x, y, and diagonal axes
void plotCirclePoints(int xc, int yc, int x, int y) {
    // The magic of 8-way symmetry!
    // Just 1 point → 8 pixels with sign changes and swaps
    putpixel(xc + x, yc + y, WHITE);   // Octant 1 (0° to 45°)
    putpixel(xc - x, yc + y, WHITE);   // Octant 4 (135° to 180°)
    putpixel(xc + x, yc - y, WHITE);   // Octant 8 (315° to 360°)
    putpixel(xc - x, yc - y, WHITE);   // Octant 5 (180° to 225°)
    putpixel(xc + y, yc + x, WHITE);   // Octant 2 (45° to 90°)
    putpixel(xc - y, yc + x, WHITE);   // Octant 3 (90° to 135°)
    putpixel(xc + y, yc - x, WHITE);   // Octant 7 (270° to 315°)
    putpixel(xc - y, yc - x, WHITE);   // Octant 6 (225° to 270°)
}

// Function: Draw a circle using the Midpoint algorithm
// Parameters: (xc, yc) = center, r = radius
void midpointCircle(int xc, int yc, int r) {
    // Start at the top-most point of the circle
    int x = 0;          // Start at x = 0
    int y = r;          // Start at y = r (top of circle)

    // Initial decision parameter
    // f(1, r-0.5) = 1² + (r-0.5)² - r² = 1 + r² - r + 0.25 - r² = 1.25 - r
    // For integer arithmetic: p₀ = 1 - r
    int p = 1 - r;

    // Plot the first set of symmetric points
    plotCirclePoints(xc, yc, x, y);

    // Loop until we've covered 45 degrees (x > y)
    // After that, the remaining points are just reflections
    while (x < y) {
        x = x + 1;      // Always step right in x

        if (p < 0) {
            // Case: Midpoint is INSIDE the circle
            // Choose pixel E (x+1, y) — keep y unchanged
            p = p + 2 * x + 3;
        } else {
            // Case: Midpoint is ON or OUTSIDE the circle
            // Choose pixel SE (x+1, y-1) — step y down
            y = y - 1;
            p = p + 2 * (x - y) + 5;
        }

        // Plot the 8 symmetric points for this (x, y)
        plotCirclePoints(xc, yc, x, y);
    }
}

// ===================================================================
// MAIN FUNCTION
// ===================================================================
int main() {
    initwindow(640, 480, "Midpoint Circle Algorithm");

    midpointCircle(300, 200, 50);
    midpointCircle(300, 200, 100);
    midpointCircle(300, 200, 150);

    outtextxy(10, 10, "Midpoint Circle Algorithm (Bresenham's Circle)");
    outtextxy(10, 30, "Concentric circles: r = 50, 100, 150");

    getch();
    closegraph();
    return 0;
}
