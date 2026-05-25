#include <graphics.h>
#include <cmath>
#include <conio.h>
#include <cstdio>

void ddaLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float xInc = (float)dx / steps;
    float yInc = (float)dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        int px = (int)(x + 0.5f);
        int py = (int)(y + 0.5f);
        putpixel(px, py, WHITE);
        x = x + xInc;
        y = y + yInc;
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
    initwindow(640, 480, "DDA Line Algorithm: Digital Differential Analyzer");

    drawAxes();

    int ox = 50, oy = getmaxy() - 50;
    int x1 = 100, y1 = 100;
    int x2 = 400, y2 = 300;

    int px1 = ox + x1, py1 = oy - y1;
    int px2 = ox + x2, py2 = oy - y2;

    setcolor(YELLOW);
    ddaLine(px1, py1, px2, py2);

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
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    float xInc = (float)dx / steps;
    float yInc = (float)dy / steps;

    setcolor(LIGHTGREEN);
    sprintf(buf, "dx = %d   dy = %d", dx, dy);
    outtextxy(10, 10, buf);
    sprintf(buf, "steps = max(|dx|,|dy|) = %d", steps);
    outtextxy(10, 30, buf);
    sprintf(buf, "xInc = dx/steps = %d/%d = %.2f", dx, steps, xInc);
    outtextxy(10, 50, buf);
    sprintf(buf, "yInc = dy/steps = %d/%d = %.2f", dy, steps, yInc);
    outtextxy(10, 70, buf);
    sprintf(buf, "Pixel loop: x += %.2f, y += %.2f each step", xInc, yInc);
    outtextxy(10, 90, buf);

    setcolor(WHITE);
    outtextxy(10, getmaxy() - 20, "Press any key to exit...");

    getch();
    closegraph();
    return 0;
}
