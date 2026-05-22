// ===================================================================
// Experiment 10: Cohen-Sutherland Line Clipping Algorithm
//
// THEORY:
// Clipping = cutting off parts of a line that are OUTSIDE a window.
// The window is a rectangle defined by xMin, xMax, yMin, yMax.
//
// REGION CODES (4 bits):
// Each endpoint gets a 4-bit code telling us where it is:
//
//     1001 | 1000 | 1010
//    ──────┼──────┼──────
//     0001 | 0000 | 0010
//    ──────┼──────┼──────
//     0101 | 0100 | 0110
//
//   Bit 3 (8) = TOP     (y > yMax)
//   Bit 2 (4) = BOTTOM  (y < yMin)
//   Bit 1 (2) = RIGHT   (x > xMax)
//   Bit 0 (1) = LEFT    (x < xMin)
//   0000      = INSIDE the window
//
// ALGORITHM:
// 1. Compute codes for both endpoints
// 2. TRIVIAL ACCEPT: both codes = 0000 → line is fully inside
// 3. TRIVIAL REJECT: codes AND ≠ 0 → both on same outside side
// 4. Otherwise: clip against one edge, replace endpoint, repeat
//
// INTERSECTION CALCULATIONS:
//   Left  (x = xMin):  y = y1 + m*(xMin - x1)
//   Right (x = xMax):  y = y1 + m*(xMax - x1)
//   Top   (y = yMin):  x = x1 + (yMin - y1)/m
//   Bottom(y = yMax):  x = x1 + (yMax - y1)/m
//   where m = (y2 - y1) / (x2 - x1)
// ===================================================================

#include <graphics.h>
#include <conio.h>

// Region code constants (bit values)
const int INSIDE = 0;   // 0000
const int LEFT   = 1;   // 0001
const int RIGHT  = 2;   // 0010
const int BOTTOM = 4;   // 0100
const int TOP    = 8;   // 1000

// Clipping window boundaries
int xMin = 150, yMin = 100;   // Top-left of window
int xMax = 450, yMax = 300;   // Bottom-right of window

// Function: Compute 4-bit region code for a point (x, y)
int computeCode(int x, int y) {
    int code = INSIDE;   // Start: assume inside

    if (x < xMin) code |= LEFT;     // Set bit 0: to the LEFT
    if (x > xMax) code |= RIGHT;    // Set bit 1: to the RIGHT
    if (y < yMin) code |= TOP;      // Set bit 3: ABOVE top
    if (y > yMax) code |= BOTTOM;   // Set bit 2: BELOW bottom

    return code;
}

// Function: Clip a line using Cohen-Sutherland and draw visible part
void cohenSutherlandClip(int x1, int y1, int x2, int y2) {
    // Get region codes for both endpoints
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    int accept = 0;   // Flag: should we draw the line?

    // Keep clipping until we accept or reject
    while (1) {
        if (code1 == 0 && code2 == 0) {
            // CASE 1: TRIVIAL ACCEPT
            // Both endpoints are inside the window
            accept = 1;
            break;
        }
        else if (code1 & code2) {
            // CASE 2: TRIVIAL REJECT
            // Both endpoints are on the same OUTSIDE side
            // (e.g., both above top = both have TOP bit set)
            // No part of line is visible
            break;
        }
        else {
            // CASE 3: LINE CROSSES WINDOW BOUNDARY
            // Pick the endpoint that's outside
            int codeOut = (code1 != 0) ? code1 : code2;

            int x, y;   // Intersection point

            // Clip against the appropriate edge
            // We check bits in order: TOP → BOTTOM → RIGHT → LEFT
            if (codeOut & TOP) {
                // Clip against TOP edge (y = yMin)
                x = x1 + (x2 - x1) * (yMin - y1) / (y2 - y1);
                y = yMin;
            }
            else if (codeOut & BOTTOM) {
                // Clip against BOTTOM edge (y = yMax)
                x = x1 + (x2 - x1) * (yMax - y1) / (y2 - y1);
                y = yMax;
            }
            else if (codeOut & RIGHT) {
                // Clip against RIGHT edge (x = xMax)
                y = y1 + (y2 - y1) * (xMax - x1) / (x2 - x1);
                x = xMax;
            }
            else if (codeOut & LEFT) {
                // Clip against LEFT edge (x = xMin)
                y = y1 + (y2 - y1) * (xMin - x1) / (x2 - x1);
                x = xMin;
            }

            // Replace the outside endpoint with the intersection point
            if (codeOut == code1) {
                x1 = x; y1 = y;
                code1 = computeCode(x1, y1);   // Recompute code
            } else {
                x2 = x; y2 = y;
                code2 = computeCode(x2, y2);   // Recompute code
            }

            // Loop back to check trivial accept/reject again
        }
    }

    // Draw the line if it was accepted (partially visible)
    if (accept) {
        setcolor(YELLOW);
        line(x1, y1, x2, y2);
    }
}

// ===================================================================
// MAIN FUNCTION
// ===================================================================
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Step 1: Draw the clipping window boundary
    setcolor(WHITE);
    rectangle(xMin, yMin, xMax, yMax);
    outtextxy(xMin + 5, yMin - 20, "Clipping Window");

    // Step 2: Define some test lines (many crossing the window)
    // Format: {x1, y1, x2, y2}
    int lines[7][4] = {
        // Partially inside lines (will be clipped)
        {50,  200, 300, 80},    // Crosses top edge
        {500, 250, 300, 350},   // Crosses bottom-right
        {100, 150, 200, 250},   // Fully inside (trivial accept)
        // Fully outside lines (will be rejected)
        {50,  50,  100, 80},    // Above window (trivial reject)
        {500, 350, 550, 400},   // Below-right (trivial reject)
        // Partially inside
        {200, 50,  350, 50},    // Above window
        {500, 150, 300, 200}    // Crosses right edge
    };

    // Step 3: Draw ALL original lines in WHITE
    setcolor(WHITE);
    for (int i = 0; i < 7; i++) {
        line(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
    }

    // Step 4: Draw only the clipped (visible) portions in YELLOW
    for (int i = 0; i < 7; i++) {
        cohenSutherlandClip(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
    }

    outtextxy(10, 10, "Experiment 10: Cohen-Sutherland Line Clipping");
    outtextxy(10, 30, "White = Original lines | Yellow = Visible portion after clip");

    getch();
    closegraph();
    return 0;
}
