// ===================================================================
// Experiment 02: Line using Slope-Intercept Formula
// Formula: y = mx + c
//
// THEORY:
// Any straight line can be written as:  y = m*x + c
//   - m = slope = (y2 - y1) / (x2 - x1)
//   - c = y-intercept = y1 - m*x1
//
// STEPS:
// 1. Take two endpoints (x1,y1) and (x2,y2)
// 2. Calculate slope m
// 3. Calculate intercept c
// 4. Loop through x from x1 to x2 (or y if line is steep)
// 5. At each step: compute y = m*x + c and plot pixel
//
// LIMITATIONS:
// - Uses floating point (slow on old hardware)
// - Vertical lines have infinite slope (special case needed)
// - Rounding errors accumulate on long lines
// ===================================================================

#include <graphics.h>    // WinBGIm graphics library
#include <cmath>         // For abs() function
#include <conio.h>       // For getch() to wait for keypress

// Function: Draw a line using y = mx + c formula
// Parameters: (x1,y1) = start point, (x2,y2) = end point
void slopeInterceptLine(int x1, int y1, int x2, int y2) {
    // Step 1: Calculate differences between endpoints
    int dx = x2 - x1;   // Horizontal distance
    int dy = y2 - y1;   // Vertical distance

    // Step 2: Handle special case - VERTICAL LINE
    // When dx = 0, the slope is infinite (can't divide by zero)
    if (dx == 0) {
        // Just iterate y from y1 to y2, keeping x constant
        int yStart = (y1 < y2) ? y1 : y2;    // Start at smaller y
        int yEnd   = (y1 < y2) ? y2 : y1;    // End at larger y
        for (int y = yStart; y <= yEnd; y++) {
            putpixel(x1, y, WHITE);           // Plot the pixel (fixed x)
        }
        return;   // Done with vertical line
    }

    // Step 3: Calculate slope (m) and y-intercept (c)
    float m = (float)dy / (float)dx;    // Slope = rise / run
    float c = y1 - m * x1;              // y-intercept

    // Step 4: Decide which axis to drive along
    // We iterate along the axis with LARGER distance
    // This prevents gaps in the line

    if (abs(dx) >= abs(dy)) {
        // Case A: Line is more horizontal (drive along x-axis)
        // Go from smaller x to larger x
        int xStart = (x1 < x2) ? x1 : x2;
        int xEnd   = (x1 < x2) ? x2 : x1;

        for (int x = xStart; x <= xEnd; x++) {
            // For each x, calculate y = mx + c
            float yExact = m * x + c;
            int yPixel = (int)(yExact + 0.5f);  // Round to nearest pixel
            putpixel(x, yPixel, WHITE);
        }
    } else {
        // Case B: Line is more vertical (drive along y-axis)
        // Go from smaller y to larger y
        int yStart = (y1 < y2) ? y1 : y2;
        int yEnd   = (y1 < y2) ? y2 : y1;

        for (int y = yStart; y <= yEnd; y++) {
            // For each y, calculate x = (y - c) / m
            float xExact = (y - c) / m;
            int xPixel = (int)(xExact + 0.5f);  // Round to nearest pixel
            putpixel(xPixel, y, WHITE);
        }
    }
}

// ===================================================================
// MAIN FUNCTION
// ===================================================================
int main() {
    // Step 1: Initialize graphics mode
    // gd = DETECT means "autodetect the best graphics driver"
    // gm will be set by initgraph
    // "" = empty path works with WinBGIm (no BGI files needed)
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Step 2: Draw a line using our slope-intercept function
    // This draws from (100, 100) to (400, 300)
    int x1 = 100, y1 = 100;   // Start point
    int x2 = 400, y2 = 300;   // End point
    slopeInterceptLine(x1, y1, x2, y2);

    // Step 3: Mark the endpoints with RED pixels
    putpixel(x1, y1, RED);
    putpixel(x2, y2, RED);

    // Step 4: Show a label on screen
    outtextxy(10, 10, "Line using Slope-Intercept Formula (y = mx + c)");
    outtextxy(10, 30, "Red dots = endpoints | White pixels = the line");

    // Step 5: Wait for keypress then close
    getch();          // Wait for user to press any key
    closegraph();     // Close the graphics window
    return 0;         // Exit program
}
