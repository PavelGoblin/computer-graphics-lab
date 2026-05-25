// ===================================================================
// Experiment 11: Sutherland-Hodgman Polygon Clipping
//
// THEORY:
// Clips a polygon against a rectangular window by processing
// ONE EDGE AT A TIME. The output of one clip stage is the
// input to the next stage.
//
// STAGES (process in this order):
//   1. Clip against LEFT edge   (x = xMin)
//   2. Clip against RIGHT edge  (x = xMax)
//   3. Clip against BOTTOM edge (y = yMax)
//   4. Clip against TOP edge    (y = yMin)
//
// FOR EACH EDGE, process consecutive vertex pairs (S → P):
//
//   Case 1: S inside,  P inside   → Output P
//   Case 2: S inside,  P outside  → Output intersection I
//   Case 3: S outside, P outside  → Output nothing
//   Case 4: S outside, P inside   → Output intersection I, then P
//
//    Inside ←────── Edge
//    ┌──────────────┐
//    │ S→P  Cases:  │
//    │ ①②  │  I← intersection
//    │ ③④  │
//    └──────────────┘
//    Outside
//
// INTERSECTION FORMULA (for edge x = k):
//   y = y1 + m*(k - x1)
// ===================================================================

#include <graphics.h>
#include <cmath>         // For round() — though we use (int)(x+0.5)
#include <conio.h>
#include <vector>        // For storing polygon vertices

using namespace std;    // So we can write "vector" instead of "std::vector"

// Structure to hold a 2D point
struct Point {
    int x, y;
};

// Clipping window boundaries
int xMin = 150, yMin = 100;
int xMax = 450, yMax = 300;

// Function: Is a point on the INSIDE of a given clipping edge?
// edge: 0=Left, 1=Right, 2=Top, 3=Bottom
bool inside(Point p, int edge) {
    switch (edge) {
        case 0: return p.x >= xMin;    // Left: must be to the right of xMin
        case 1: return p.x <= xMax;    // Right: must be to the left of xMax
        case 2: return p.y >= yMin;    // Top: must be below yMin
        case 3: return p.y <= yMax;    // Bottom: must be above yMax
    }
    return false;
}

// Function: Find intersection of line segment (p1→p2) with clipping edge
Point intersect(Point p1, Point p2, int edge) {
    Point result;
    float m;    // Slope of the line

    // Calculate slope (handle vertical lines)
    if (p2.x != p1.x)
        m = (float)(p2.y - p1.y) / (float)(p2.x - p1.x);
    else
        m = 1e10f;    // Very large number = near-vertical

    // Compute intersection based on which edge we're clipping against
    switch (edge) {
        case 0: // INTERSECTION WITH LEFT edge (x = xMin)
            result.x = xMin;
            result.y = (int)(p1.y + m * (xMin - p1.x) + 0.5f);
            break;
        case 1: // INTERSECTION WITH RIGHT edge (x = xMax)
            result.x = xMax;
            result.y = (int)(p1.y + m * (xMax - p1.x) + 0.5f);
            break;
        case 2: // INTERSECTION WITH TOP edge (y = yMin)
            result.y = yMin;
            if (p2.x != p1.x)
                result.x = (int)(p1.x + (yMin - p1.y) / m + 0.5f);
            else
                result.x = p1.x;    // Vertical line: x doesn't change
            break;
        case 3: // INTERSECTION WITH BOTTOM edge (y = yMax)
            result.y = yMax;
            if (p2.x != p1.x)
                result.x = (int)(p1.x + (yMax - p1.y) / m + 0.5f);
            else
                result.x = p1.x;
            break;
    }
    return result;
}

// Function: Clip a polygon against a SINGLE edge
// Returns a new polygon (the clipped result)
vector<Point> clipAgainstEdge(vector<Point> poly, int edge) {
    vector<Point> result;   // Store output vertices here
    int n = poly.size();    // Number of vertices

    if (n == 0) return result;   // Empty polygon? Nothing to do

    // Process each edge of the polygon (each pair of consecutive vertices)
    for (int i = 0; i < n; i++) {
        Point current = poly[i];                  // Current vertex S
        Point next    = poly[(i + 1) % n];         // Next vertex P (wraps around)

        bool currInside = inside(current, edge);   // Is S inside?
        bool nextInside = inside(next, edge);      // Is P inside?

        if (currInside && nextInside) {
            // CASE 1: Both vertices are INSIDE
            // → Output the next vertex (P)
            result.push_back(next);
        }
        else if (currInside && !nextInside) {
            // CASE 2: INSIDE → OUTSIDE
            // → Output the intersection point (where line crosses the edge)
            result.push_back(intersect(current, next, edge));
        }
        else if (!currInside && nextInside) {
            // CASE 4: OUTSIDE → INSIDE
            // → Output intersection first, then the next vertex
            result.push_back(intersect(current, next, edge));
            result.push_back(next);
        }
        // CASE 3: Both OUTSIDE → Output nothing
    }

    return result;
}

// Function: Draw a polygon on screen
void drawPolygon(vector<Point> poly, int color) {
    if (poly.size() < 3) return;    // A polygon needs at least 3 points
    setcolor(color);
    for (size_t i = 0; i < poly.size(); i++) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % poly.size()];
        line(p1.x, p1.y, p2.x, p2.y);
    }
}

// ===================================================================
// MAIN FUNCTION
// ===================================================================
int main() {
    initwindow(640, 480, "Sutherland-Hodgman Polygon Clipping");

    // Step 1: Draw clipping window
    setcolor(WHITE);
    rectangle(xMin, yMin, xMax, yMax);
    outtextxy(xMin + 5, yMin - 20, "Clipping Window");

    // Step 2: Define a polygon (8 vertices — can be concave!)
    vector<Point> polygon;
    polygon.push_back({80,  80});    // Vertex 0: top-left
    polygon.push_back({200, 50});    // Vertex 1: top
    polygon.push_back({350, 120});   // Vertex 2: upper-right
    polygon.push_back({500, 100});   // Vertex 3: far right
    polygon.push_back({520, 250});   // Vertex 4: bottom-right
    polygon.push_back({400, 350});   // Vertex 5: bottom
    polygon.push_back({100, 280});   // Vertex 6: bottom-left
    polygon.push_back({50,  200});   // Vertex 7: left

    // Step 3: Draw the ORIGINAL polygon in WHITE
    drawPolygon(polygon, WHITE);

    // Step 4: Clip against all 4 window edges sequentially
    vector<Point> clipped = polygon;           // Start with original
    for (int edge = 0; edge < 4; edge++) {     // Left → Right → Bottom → Top
        clipped = clipAgainstEdge(clipped, edge);
    }

    // Step 5: Draw the CLIPPED polygon in YELLOW
    drawPolygon(clipped, YELLOW);

    // Label
    outtextxy(10, 10, "Experiment 11: Sutherland-Hodgman Polygon Clipping");
    outtextxy(10, 30, "White = Original polygon | Yellow = After clipping");

    // Draw label near clipped result
    if (clipped.size() >= 3) {
        int labelX = 0, labelY = 0;
        for (auto p : clipped) { labelX += p.x; labelY += p.y; }
        labelX /= clipped.size();
        labelY /= clipped.size();
        outtextxy(labelX - 30, labelY, "Clipped");
    }

    getch();
    closegraph();
    return 0;
}
