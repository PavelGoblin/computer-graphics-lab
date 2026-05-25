// ===================================================================
// Experiment 04: Bresenham's Line Algorithm
//
// THEORY:
// Bresenham's algorithm is the GOLD STANDARD for line drawing.
// It uses ONLY INTEGER arithmetic — no floating point, no rounding!
// This makes it extremely fast (hardware-friendly).
//
// THE KEY INSIGHT:
// At each step, we have TWO possible pixels to choose from.
// We pick the one CLOSER to the true line using a DECISION PARAMETER.
//
// For a line with slope 0 < m < 1 (going right and down):
//   - If we're at pixel (x, y), the next pixel is either:
//     Option E:  (x+1, y)   ← directly to the right
//     Option NE: (x+1, y+1) ← diagonally right-down
//
// DECISION PARAMETER (p):
//   p = 2*dy - dx         (initial value)
//   If p < 0:  plot E,    p += 2*dy
//   If p >= 0: plot NE,   p += 2*(dy - dx)
//
// GENERALIZATION TO ALL OCTANTS:
// The algorithm works in all 8 octants by tracking:
//   - sx, sy: direction (+1 or -1) for x and y
//   - swapped: whether we swapped x and y (for steep slopes)
// ===================================================================

#include <graphics.h>
#include <conio.h>

// Function: Draw a line using Bresenham's integer algorithm
// Works in ALL 8 octants (any direction, any slope)
void bresenhamLine(int x1, int y1, int x2, int y2) {
    // Step 1: Calculate absolute differences
    // abs() = always positive, gives us the magnitude of movement
    int dx = abs(x2 - x1);    // Total horizontal distance
    int dy = abs(y2 - y1);    // Total vertical distance

    // Step 2: Determine direction of movement
    // If x2 > x1, we move RIGHT (sx = +1), otherwise LEFT (sx = -1)
    int sx = (x1 < x2) ? 1 : -1;
    // Same for y: UP (sy = -1 in screen coords) or DOWN (sy = +1)
    int sy = (y1 < y2) ? 1 : -1;

    // Step 3: Handle steep slopes (|dy| > |dx|)
    // For steep lines, we swap the roles of x and y
    // This means we step along y instead of x
    int swapped = 0;    // Flag: did we swap?
    if (dy > dx) {
        // Swap dx and dy — now dx is the "driving axis"
        int temp = dx;
        dx = dy;
        dy = temp;
        swapped = 1;    // Remember we swapped for later
    }

    // Step 4: Initialize the decision parameter
    // This tells us which pixel is closer to the true line
    int p = 2 * dy - dx;

    // Step 5: Start at the first endpoint
    int x = x1, y = y1;

    // Step 6: Walk along the driving axis
    // We take exactly dx steps (1 pixel per step on the driving axis)
    for (int i = 0; i <= dx; i++) {
        // Plot the current pixel
        putpixel(x, y, WHITE);

        // Decision time: should we step on the other axis too?
        // p >= 0 means the diagonal pixel is closer to the true line
        while (p >= 0) {
            // Move along the non-driving axis
            if (swapped == 1)
                x = x + sx;     // If swapped, x is the non-driving axis
            else
                y = y + sy;     // If not swapped, y is the non-driving axis

            // Update decision parameter (we took the diagonal step)
            p = p - 2 * dx;
        }

        // Always move along the driving axis
        if (swapped == 1)
            y = y + sy;         // If swapped, y is the driving axis
        else
            x = x + sx;         // If not swapped, x is the driving axis

        // Update decision parameter (we took the axial step)
        p = p + 2 * dy;
    }
}

// ===================================================================
// MAIN FUNCTION
// ===================================================================
int main() {
    initwindow(640, 480, "Bresenham Line Algorithm");

    int cx = 300, cy = 200;

    bresenhamLine(cx, cy, cx + 150, cy);
    bresenhamLine(cx, cy, cx + 100, cy - 80);
    bresenhamLine(cx, cy, cx, cy - 150);
    bresenhamLine(cx, cy, cx - 100, cy - 80);
    bresenhamLine(cx, cy, cx - 150, cy);
    bresenhamLine(cx, cy, cx - 100, cy + 80);
    bresenhamLine(cx, cy, cx, cy + 150);
    bresenhamLine(cx, cy, cx + 100, cy + 80);

    outtextxy(10, 10, "Bresenham's Line Algorithm (Integer Arithmetic)");
    outtextxy(10, 30, "Lines in all 8 octants from center (300, 200)");

    getch();
    closegraph();
    return 0;
}
