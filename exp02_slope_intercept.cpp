#include <graphics.h>
#include <cmath>
#include <conio.h>
#include <cstdio>

void slopeInterceptLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dx == 0) {
        int yStart = (y1 < y2) ? y1 : y2;
        int yEnd   = (y1 < y2) ? y2 : y1;
        for (int y = yStart; y <= yEnd; y++)
            putpixel(x1, y, WHITE);
        return;
    }

    float m = (float)dy / (float)dx;
    float c = y1 - m * x1;

    if (abs(dx) >= abs(dy)) {
        int xStart = (x1 < x2) ? x1 : x2;
        int xEnd   = (x1 < x2) ? x2 : x1;
        for (int x = xStart; x <= xEnd; x++) {
            float yExact = m * x + c;
            int yPixel = (int)(yExact + 0.5f);
            putpixel(x, yPixel, WHITE);
        }
    } else {
        int yStart = (y1 < y2) ? y1 : y2;
        int yEnd   = (y1 < y2) ? y2 : y1;
        for (int y = yStart; y <= yEnd; y++) {
            float xExact = (y - c) / m;
            int xPixel = (int)(xExact + 0.5f);
            putpixel(xPixel, y, WHITE);
        }
    }
}

void drawAxes() {
    int w = getmaxx();
    int h = getmaxy();
    int ox = 50, oy = h - 50;

    setcolor(LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);

    // X-axis
    line(ox, oy, w - 20, oy);
    line(w - 20, oy, w - 30, oy - 5);
    line(w - 20, oy, w - 30, oy + 5);
    outtextxy(w - 30, oy + 8, "X");

    // Y-axis
    line(ox, oy, ox, 20);
    line(ox, 20, ox - 5, 30);
    line(ox, 20, ox + 5, 30);
    outtextxy(ox - 10, 10, "Y");

    // Origin
    outtextxy(ox - 20, oy + 5, "O");

    // Tick marks
    setcolor(DARKGRAY);
    for (int i = 1; i <= 10; i++) {
        int x = ox + i * 50;
        int y = oy - i * 50;
        if (x <= w - 20) {
            line(x, oy - 3, x, oy + 3);
            char buf[10];
            sprintf(buf, "%d", i * 50);
            outtextxy(x - 8, oy + 6, buf);
        }
        if (y >= 20) {
            line(ox - 3, y, ox + 3, y);
            char buf[10];
            sprintf(buf, "%d", i * 50);
            outtextxy(ox - 35, y - 5, buf);
        }
    }
}

int main() {
    initwindow(640, 480, "Slope-Intercept: y = mx + c");

    drawAxes();

    int ox = 50, oy = getmaxy() - 50;
    int x1 = 100, y1 = 100;
    int x2 = 400, y2 = 300;

    int px1 = ox + x1, py1 = oy - y1;
    int px2 = ox + x2, py2 = oy - y2;

    setcolor(YELLOW);
    slopeInterceptLine(px1, py1, px2, py2);

    setcolor(RED);
    circle(px1, py1, 4);
    circle(px2, py2, 4);
    setfillstyle(SOLID_FILL, RED);
    floodfill(px1, py1, RED);
    floodfill(px2, py2, RED);

    setcolor(LIGHTRED);
    char buf[64];
    sprintf(buf, "A(%d,%d)", x1, y1);
    outtextxy(px1 + 8, py1 - 10, buf);
    sprintf(buf, "B(%d,%d)", x2, y2);
    outtextxy(px2 + 8, py2 - 10, buf);

    int dx = x2 - x1, dy = y2 - y1;
    float m = (float)dy / (float)dx;
    float c = y1 - m * x1;

    setcolor(LIGHTGREEN);
    sprintf(buf, "dx = %d   dy = %d", dx, dy);
    outtextxy(10, 10, buf);
    sprintf(buf, "m = dy/dx = %d/%d = %.2f", dy, dx, m);
    outtextxy(10, 30, buf);
    sprintf(buf, "c = y1 - m*x1 = %d - (%.2f)*%d = %.2f", y1, m, x1, c);
    outtextxy(10, 50, buf);
    sprintf(buf, "Equation: y = %.2fx + %.2f", m, c);
    outtextxy(10, 70, buf);

    sprintf(buf, "At x = %d, y = %.2f*%d + %.2f = %.0f", x1, m, x1, c, m * x1 + c);
    outtextxy(10, 95, buf);
    sprintf(buf, "At x = %d, y = %.2f*%d + %.2f = %.0f", x2, m, x2, c, m * x2 + c);
    outtextxy(10, 115, buf);

    setcolor(WHITE);
    outtextxy(10, getmaxy() - 20, "Press any key to exit...");

    getch();
    closegraph();
    return 0;
}
