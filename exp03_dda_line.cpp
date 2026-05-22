// ===================================================================
// Experiment 03: DDA (Digital Differential Analyzer) Line Algorithm
//
// THEORY:
// DDA is an INCREMENTAL algorithm. Instead of recalculating
// y = mx+c at every step (which needs multiplication), we just
// ADD a small increment to the previous value.
//
// KEY IDEA:
//   x_new = x_old + x_increment
//   y_new = y_old + y_increment
//
// STEPS:
// 1. Calculate dx = x2-x1, dy = y2-y1
// 2. steps = max(|dx|, |dy|)  ← ensures no gaps
// 3. x_inc = dx/steps, y_inc = dy/steps
// 4. Start at (x1, y1)
// 5. For each step: plot(round(x), round(y)), then x+=x_inc, y+=y_inc
//
// WHY steps = max(|dx|, |dy|)?
// - If we take |dx| steps, we step 1 pixel at a time along x
// - If we take |dy| steps, we step 1 pixel at a time along y
// - Taking the MAX ensures we step 1 pixel along the LONGER axis
// - The shorter axis gets fractional steps (no gaps)
//
// ADVANTAGES: Simple, works for any slope
// DISADVANTAGES: Floating point (rounding errors), slower than integer
// ===================================================================

#include <graphics.h>    // WinBGIm graphics functions
#include <cmath>         // For abs() function
#include <conio.h>       // For getch()

// Function: Draw a line using DDA algorithm
// Parameters: (x1,y1) to (x2,y2) = endpoints of the line
void ddaLine(int x1, int y1, int x2, int y2) {
    // Step 1: Calculate the total distance in x and y
    int dx = x2 - x1;   // How far right/left?
    int dy = y2 - y1;   // How far up/down?

    // Step 2: Determine how many steps we need
    // We take 1 step per pixel along the LONGEST axis
    int steps;
    if (abs(dx) > abs(dy)) {
        steps = abs(dx);   // More horizontal → step along x
    } else {
        steps = abs(dy);   // More vertical → step along y
    }

    // Step 3: Calculate how much x and y change PER STEP
    // These are fractional values (less than 1.0 for the shorter axis)
    float xInc = (float)dx / steps;   // x increment per step
    float yInc = (float)dy / steps;   // y increment per step

    // Step 4: Start at the first endpoint
    float x = x1;   // Current x position (fractional)
    float y = y1;   // Current y position (fractional)

    // Step 5: Loop through each step
    // At each step, plot the nearest pixel and move forward
    for (int i = 0; i <= steps; i++) {
        // Round to nearest integer pixel coordinates
        int px = (int)(x + 0.5f);
        int py = (int)(y + 0.5f);

        // Plot the pixel at the current position
        putpixel(px, py, WHITE);

        // Move to the next position (incremental step)
        x = x + xInc;
        y = y + yInc;
    }

    // Note: No explicit loop for x or y direction!
    // xInc and yInc handle direction automatically:
    //   - Positive dx → xInc is positive (moving right)
    //   - Negative dx → xInc is negative (moving left)
    //   - Same for y
}

// ===================================================================
// MAIN FUNCTION
// ===================================================================
int main() {
    // Step 1: Initialize graphics window
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Step 2: Draw multiple lines using DDA to show it works
    // in different directions

    // A horizontal line (left to right)
    ddaLine(50, 200, 550, 200);
    // Explanation: dx=500, dy=0, steps=500
    // xInc=1.0, yInc=0.0 → moves right only

    // A vertical line (top to bottom)
    ddaLine(300, 50, 300, 350);
    // Explanation: dx=0, dy=300, steps=300
    // xInc=0.0, yInc=1.0 → moves down only

    // A diagonal line (positive slope)
    ddaLine(100, 100, 500, 300);
    // Explanation: dx=400, dy=200, steps=400
    // xInc=1.0, yInc=0.5 → moves right and slowly down

    // A diagonal line (negative slope)
    ddaLine(100, 300, 500, 100);
    // Explanation: dx=400, dy=-200, steps=400
    // xInc=1.0, yInc=-0.5 → moves right and slowly up

    // Show labels
    outtextxy(10, 10, "DDA (Digital Differential Analyzer) Algorithm");
    outtextxy(10, 30, "Horizontal, Vertical, Positive & Negative Slope");

    // Wait and close
    getch();
    closegraph();
    return 0;
}
