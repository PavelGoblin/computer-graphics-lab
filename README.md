# Computer Graphics and Multimedia System Lab (CSE41P8)

All experiments implemented in **C++** (WinBGIm) and **Python** (matplotlib).

---

## Run Instructions

```bash
# ── C++ (requires WinBGIm setup) ──
.\setup.ps1          # One-time setup
.\run.ps1 2          # Run experiment 2 (experiment number 2-13)
.\menu.ps1           # Interactive menu

# ── Python (requires matplotlib) ──
pip install matplotlib pillow numpy
python exp02_slope_intercept.py   # Replace with any exp*.py
```

---

## Experiment 1: Input and Output Devices

📄 **Theory only** — [`exp01_io_devices.md`](exp01_io_devices.md)

---

## Experiment 2: Line Drawing using Slope-Intercept Formula

**Files:** `exp02_slope_intercept.cpp` · `exp02_slope_intercept.py`

### Theory

The slope-intercept form is the most basic way to represent a straight line:

```
y = m·x + c
```

Where:
- **m** (slope) = (y₂ − y₁) / (x₂ − x₁) — measures steepness
- **c** (y-intercept) = y₁ − m·x₁ — where line crosses Y-axis

**How it works for drawing:**
- If |dx| ≥ |dy| (gentle slope), loop over x and compute y = round(m·x + c)
- If |dx| < |dy| (steep slope), loop over y and compute x = round((y − c) / m)
- For vertical lines (dx = 0), just iterate y from y₁ to y₂

### Algorithm

```
INPUT: (x₁, y₁), (x₂, y₂)
OUTPUT: Set of pixel coordinates

1. dx = x₂ − x₁, dy = y₂ − y₁
2. IF dx == 0 (vertical line):
      FOR y = min(y₁,y₂) TO max(y₁,y₂):
         PLOT(x₁, y)
3. ELSE:
      m = dy / dx
      c = y₁ − m·x₁
      IF |dx| ≥ |dy|:
         FOR x = min(x₁,x₂) TO max(x₁,x₂):
            y = ROUND(m·x + c)
            PLOT(x, y)
      ELSE:
         FOR y = min(y₁,y₂) TO max(y₁,y₂):
            x = ROUND((y − c) / m)
            PLOT(x, y)
```

### Example

**Points:** A(2, 3), B(8, 11)

```
dx = 6, dy = 8
m = 8/6 = 1.333...
c = 3 − 1.333×2 = 0.334

Since |dx| < |dy| (6 < 8), iterate over y:

 y  |  x = (y − 0.334)/1.333  | round(x) | pixel
────┼──────────────────────────┼──────────┼───────
 3  |  2.0                     |    2     | (2,3)
 4  |  2.75                    |    3     | (3,4)
 5  |  3.5                     |    4     | (4,5)
 6  |  4.25                    |    4     | (4,6)
 7  |  5.0                     |    5     | (5,7)
 8  |  5.75                    |    6     | (6,8)
 9  |  6.5                     |    7     | (7,9)
10  |  7.25                    |    7     | (7,10)
11  |  8.0                     |    8     | (8,11)
```

### Analysis

| Aspect | Rating |
|--------|--------|
| Arithmetic | Floating-point (slow on old hardware) |
| Vertical lines | Requires special case (dx = 0) |
| Accumulated error | Yes — repeated multiplication drifts |
| Rounding | Required at each step |

### Python Code

```python
import matplotlib.pyplot as plt

def slope_intercept_line(x1, y1, x2, y2):
    dx, dy = x2 - x1, y2 - y1
    if dx == 0:
        y_start = min(y1, y2)
        y_end = max(y1, y2)
        return [(x1, y) for y in range(y_start, y_end + 1)], 0, 0

    m = dy / dx
    c = y1 - m * x1
    pixels = []

    if abs(dx) >= abs(dy):
        x_start = min(x1, x2)
        x_end = max(x1, x2)
        for x in range(x_start, x_end + 1):
            y_exact = m * x + c
            pixels.append((x, round(y_exact)))
    else:
        y_start = min(y1, y2)
        y_end = max(y1, y2)
        for y in range(y_start, y_end + 1):
            x_exact = (y - c) / m
            pixels.append((round(x_exact), y))

    return pixels, m, c


def run():
    x1, y1 = 100, 100
    x2, y2 = 400, 300
    result = slope_intercept_line(x1, y1, x2, y2)
    pixels, m, c = result

    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("Slope-Intercept: y = mx + c")

    xs, ys = zip(*pixels)
    ax.scatter(xs, ys, c="yellow", s=30, label="Line pixels", zorder=3)
    ax.plot([x1, x2], [y1, y2], "r--", linewidth=1, alpha=0.5, label="True line")

    ax.scatter([x1, x2], [y1, y2], c="red", s=80, zorder=4)
    ax.annotate(f"A({x1},{y1})", (x1, y1), xytext=(8, 5),
                textcoords="offset points", color="red", fontsize=9)
    ax.annotate(f"B({x2},{y2})", (x2, y2), xytext=(8, 5),
                textcoords="offset points", color="red", fontsize=9)

    dx, dy = x2 - x1, y2 - y1
    info = (
        f"dx = {dx}   dy = {dy}\n"
        f"m = dy/dx = {dy}/{dx} = {m:.2f}\n"
        f"c = y1 - m*x1 = {y1} - ({m:.2f})*{x1} = {c:.2f}\n"
        f"Equation: y = {m:.2f}x + {c:.2f}"
    )
    ax.text(0.02, 0.98, info, transform=ax.transAxes,
            fontsize=9, verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="wheat", alpha=0.8))

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.grid(True, alpha=0.3)
    ax.legend(fontsize=9)
    ax.set_aspect("equal")
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    run()
```

### Output

![Slope-Intercept Line](assets/02_slope_intercept.png)

---

## Experiment 3: Line Drawing using DDA Algorithm

**Files:** `exp03_dda_line.cpp` · `exp03_dda_line.py`

### Theory

DDA (Digital Differential Analyzer) is an incremental algorithm. Instead of computing y from scratch at each x (which requires multiplication), DDA **adds a small increment** to the previous value.

**Key insight:**
- If a line has slope m = dy/dx, then for each unit step in x, y changes by m
- We choose the number of steps = max(|dx|, |dy|) so we take exactly one step per pixel along the dominant axis
- At each step: x += x_inc, y += y_inc, where x_inc = dx/steps, y_inc = dy/steps

**Why steps = max(|dx|, |dy|)?**
- If |dx| > |dy|, stepping by 1 in x gives steps = |dx|, and y_inc = dy/dx = m (fractional)
- If |dy| > |dx|, stepping by 1 in y gives steps = |dy|, and x_inc = dx/dy = 1/m (fractional)
- This guarantees we never skip pixels — the dominant axis always moves by exactly 1

### Algorithm

```
INPUT: (x₁, y₁), (x₂, y₂)
OUTPUT: Set of pixel coordinates

1. dx = x₂ − x₁, dy = y₂ − y₁
2. steps = max(|dx|, |dy|)
3. x_inc = dx / steps
   y_inc = dy / steps
4. x = x₁, y = y₁
5. FOR i = 0 TO steps:
      PLOT(ROUND(x), ROUND(y))
      x = x + x_inc
      y = y + y_inc
```

### Example

**Points:** A(3, 2), B(9, 7)

```
dx = 6, dy = 5
steps = max(6, 5) = 6
x_inc = 6/6 = 1.0
y_inc = 5/6 = 0.833

Step |   x   |   y   | round(x,y) | pixel
─────┼───────┼───────┼────────────┼───────
  0  | 3.000 | 2.000 |   (3, 2)   | (3,2)
  1  | 4.000 | 2.833 |   (4, 3)   | (4,3)
  2  | 5.000 | 3.667 |   (5, 4)   | (5,4)
  3  | 6.000 | 4.500 |   (6, 5)   | (6,5)
  4  | 7.000 | 5.333 |   (7, 5)   | (7,5)
  5  | 8.000 | 6.167 |   (8, 6)   | (8,6)
  6  | 9.000 | 7.000 |   (9, 7)   | (9,7)
```

### Analysis

| Advantage | Disadvantage |
|-----------|-------------|
| Simple to implement | Floating-point arithmetic (slow) |
| No special cases for slope | Rounding error accumulates over long lines |
| Works for any slope | Round() needed at every step |
| No integer overflow | Slower than integer-only algorithms |

### Python Code

```python
import matplotlib.pyplot as plt

def dda_line(x1, y1, x2, y2):
    dx = x2 - x1
    dy = y2 - y1
    steps = max(abs(dx), abs(dy))
    x_inc = dx / steps
    y_inc = dy / steps

    x, y = float(x1), float(y1)
    pixels = []
    for _ in range(steps + 1):
        pixels.append((round(x), round(y)))
        x += x_inc
        y += y_inc
    return pixels


def run():
    x1, y1 = 100, 100
    x2, y2 = 400, 300
    pixels = dda_line(x1, y1, x2, y2)

    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("DDA Line Algorithm: Digital Differential Analyzer")

    xs, ys = zip(*pixels)
    ax.scatter(xs, ys, c="yellow", s=30, label="DDA Pixels", zorder=3)
    ax.plot([x1, x2], [y1, y2], "r--", linewidth=1, alpha=0.5, label="True line")

    ax.scatter([x1, x2], [y1, y2], c="red", s=80, zorder=4)
    ax.annotate(f"A({x1},{y1})", (x1, y1), xytext=(8, 5), textcoords="offset points", color="red", fontsize=9)
    ax.annotate(f"B({x2},{y2})", (x2, y2), xytext=(8, 5), textcoords="offset points", color="red", fontsize=9)

    dx, dy = x2 - x1, y2 - y1
    steps = max(abs(dx), abs(dy))
    x_inc = dx / steps
    y_inc = dy / steps

    info = (
        f"dx = {dx}   dy = {dy}\n"
        f"steps = max(|dx|,|dy|) = {steps}\n"
        f"x_inc = dx/steps = {dx}/{steps} = {x_inc:.2f}\n"
        f"y_inc = dy/steps = {dy}/{steps} = {y_inc:.2f}"
    )
    ax.text(0.02, 0.98, info, transform=ax.transAxes, fontsize=9,
            verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="wheat", alpha=0.8))

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.grid(True, alpha=0.3)
    ax.legend(fontsize=9)
    ax.set_aspect("equal")
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    run()
```

### Output

![DDA Line Algorithm](assets/03_dda_line.png)

---

## Experiment 4: Line Drawing using Bresenham's Algorithm

**Files:** `exp04_bresenham_line.cpp` · `exp04_bresenham_line.py`

### Theory

Bresenham's algorithm is the **gold standard** for line drawing. It uses **only integer arithmetic** — no floating point, no rounding, no multiplication by slope.

**The Key Insight:**
At pixel (x, y), the next pixel can be either:
- **E** (x+1, y) — directly to the right
- **NE** (x+1, y+1) — diagonally up-right

We decide by comparing the midpoint M = (x+1, y+0.5) against the true line y = m·x + c:

```
If M is below the line → NE is closer → plot (x+1, y+1)
If M is above the line → E is closer → plot (x+1, y)
```

**Decision Parameter Derivation:**
- For line from (x₁,y₁) to (x₂,y₂) with 0 < m < 1:
- f(x, y) = y − m·x − c = 0 (line equation in implicit form)
- At midpoint (x+1, y+0.5): p = f(x+1, y+0.5) = 2·dy·(x+1) − 2·dx·(y+0.5) + 2·c·dx
- Simplified to integer arithmetic:
  - p₀ = 2·dy − dx
  - If p < 0: plot E, p += 2·dy
  - If p ≥ 0: plot NE, p += 2·(dy − dx)

### Algorithm (Octant 1: 0 < m < 1)

```
INPUT: (x₁, y₁), (x₂, y₂)  where x₁ < x₂ and 0 < (y₂−y₁) < (x₂−x₁)
OUTPUT: Set of pixel coordinates

1. dx = x₂ − x₁, dy = y₂ − y₁
2. p = 2·dy − dx
3. x = x₁, y = y₁
4. FOR each x from x₁ TO x₂:
      PLOT(x, y)
      IF p < 0:
         p = p + 2·dy           (go EAST)
      ELSE:
         y = y + 1
         p = p + 2·(dy − dx)    (go NORTH-EAST)
```

### Generalization to All 8 Octants

```
1. dx = |x₂ − x₁|, dy = |y₂ − y₁|
2. sx = sign(x₂ − x₁), sy = sign(y₂ − y₁)     ← direction of movement
3. IF dy > dx (steep slope):
      SWAP dx, dy
      swapped = True                            ← x and y axes swapped
4. p = 2·dy − dx
5. x = x₁, y = y₁
6. FOR i = 0 TO dx:
      PLOT(x, y)
      WHILE p ≥ 0:                              ← diagonal step needed
         IF swapped: x += sx  ELSE: y += sy
         p = p − 2·dx
      IF swapped: y += sy  ELSE: x += sx        ← always step on driving axis
      p = p + 2·dy
```

### Example

**Points:** A(2, 2), B(8, 5)

```
dx = 6, dy = 3
p₀ = 2·3 − 6 = 0

 x | y |  p before | action  |  p after | pixel
───┼───┼───────────┼─────────┼──────────┼───────
 2 | 2 |     0     | NE, y++ | 2(3-6)=-6| (2,2)
 3 | 3 |    -6     | E       | -6+6=0   | (3,3)
 4 | 3 |     0     | NE, y++ | 2(3-6)=-6| (4,3)
 5 | 4 |    -6     | E       | -6+6=0   | (5,4)
 6 | 4 |     0     | NE, y++ | 2(3-6)=-6| (6,4)
 7 | 5 |    -6     | E       | -6+6=0   | (7,5)
 8 | 5 |     —     | done    |    —     | (8,5)
```

### Analysis

| Advantage | Disadvantage |
|-----------|-------------|
| Only integer addition/subtraction | Slightly more complex to implement |
| No division, no rounding | Must handle all 8 octants |
| No accumulated error | — |
| Fast — ideal for hardware | — |
| Exact results | — |

### Python Code

```python
import matplotlib.pyplot as plt

def bresenham_line(x1, y1, x2, y2):
    dx = abs(x2 - x1)
    dy = abs(y2 - y1)
    sx = 1 if x1 < x2 else -1
    sy = 1 if y1 < y2 else -1

    swapped = 0
    if dy > dx:
        dx, dy = dy, dx
        swapped = 1

    p = 2 * dy - dx
    x, y = x1, y1
    pixels = []

    for _ in range(dx + 1):
        pixels.append((x, y))
        while p >= 0:
            if swapped:
                x += sx
            else:
                y += sy
            p -= 2 * dx
        if swapped:
            y += sy
        else:
            x += sx
        p += 2 * dy

    return pixels


def run():
    cx, cy = 300, 200
    endpoints = [
        (cx, cy, cx + 150, cy), (cx, cy, cx + 100, cy - 80),
        (cx, cy, cx, cy - 150), (cx, cy, cx - 100, cy - 80),
        (cx, cy, cx - 150, cy), (cx, cy, cx - 100, cy + 80),
        (cx, cy, cx, cy + 150), (cx, cy, cx + 100, cy + 80),
    ]

    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("Bresenham Line Algorithm (Integer Arithmetic)")

    colors = plt.cm.tab10.colors
    for i, (x1, y1, x2, y2) in enumerate(endpoints):
        pixels = bresenham_line(x1, y1, x2, y2)
        xs, ys = zip(*pixels)
        ax.scatter(xs, ys, color=colors[i % len(colors)], s=20, zorder=3)

    ax.scatter([cx], [cy], c="red", s=100, zorder=4, marker="o")
    ax.annotate(f"Center ({cx},{cy})", (cx, cy), xytext=(8, 5),
                textcoords="offset points", color="red", fontsize=9, fontweight="bold")

    ax.text(0.02, 0.98, "Bresenham's Line Algorithm\nLines in all 8 octants from center",
            transform=ax.transAxes, fontsize=10, verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="lightcyan", alpha=0.8))

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.grid(True, alpha=0.3)
    ax.set_aspect("equal")
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    run()
```

### Output

![Bresenham Line Algorithm](assets/04_bresenham_line.png)

---

## Experiment 5: Midpoint Circle Algorithm

**Files:** `exp05_midpoint_circle.cpp` · `exp05_midpoint_circle.py`

### Theory

The midpoint (Bresenham's) circle algorithm uses the implicit circle equation:

```
f(x, y) = x² + y² − r² = 0
```

**Decision function:**
- f(x, y) < 0 → point is INSIDE the circle
- f(x, y) = 0 → point is ON the circle
- f(x, y) > 0 → point is OUTSIDE the circle

**8-Way Symmetry:**
If (x, y) is on the circle, so are:
```
(±x, ±y), (±y, ±x)  →  8 points total
```
We only compute 1/8 of the circle (0° to 45°) and reflect.

**Decision Parameter:**
Starting at (0, r):
- p₀ = 1 − r (integer version of 5/4 − r)
- At each step x → x+1:
  - If p < 0 (midpoint inside): pixel E (x+1, y), p += 2·x + 3
  - If p ≥ 0 (midpoint on/outside): pixel SE (x+1, y−1), p += 2·(x−y) + 5

### Algorithm

```
INPUT: Center (xc, yc), Radius r
OUTPUT: Set of pixel coordinates (using 8-way symmetry)

1. x = 0, y = r
2. p = 1 − r
3. PLOT 8 symmetric points: (±x, ±y), (±y, ±x)
4. WHILE x < y:
      x = x + 1
      IF p < 0:
         p = p + 2·x + 3          (point E)
      ELSE:
         y = y − 1
         p = p + 2·(x − y) + 5    (point SE)
      PLOT 8 symmetric points
```

### Example

**Center (0, 0), r = 10**

```
p₀ = 1 − 10 = −9

 x | y |  p before | action |  p after | plotted (8 symmetric)
───┼───┼───────────┼────────┼──────────┼─────────────────────────
 0 |10 |     —     |  init  |    -9    | (0,10), (10,0), (0,-10), (-10,0)
 1 |10 |    -9     |   E    | -9+5=-4  | (±1,±10), (±10,±1)
 2 |10 |    -4     |   E    | -4+7=3   | (±2,±10), (±10,±2)
 3 |10 |     3     |  SE, y=9| 3+2(3-10)+5=-6| (±3,±10), (±10,±3)
 4 | 9 |    -6     |   E    | -6+11=5  | (±4,±9), (±9,±4)
 5 | 9 |     5     |  SE, y=8| 5+2(5-9)+5=2 | (±5,±9), (±9,±5)
 6 | 8 |     2     |  SE, y=7| 2+2(6-7)+5=5 | (±6,±8), (±8,±6)
 7 | 7 |     5     |  SE, y=6| 5+2(7-6)+5=12| (±7,±7)  ← x > y, stop
```

### Analysis

| Aspect | Rating |
|--------|--------|
| Arithmetic | Integer only |
| Symmetry | 8-way — 1/8th computation |
| Speed | Very fast |
| Accuracy | Exact for integer radii |

### Python Code

```python
import matplotlib.pyplot as plt

def plot_circle_points(ax, xc, yc, x, y):
    pts = [
        (xc + x, yc + y), (xc - x, yc + y),
        (xc + x, yc - y), (xc - x, yc - y),
        (xc + y, yc + x), (xc - y, yc + x),
        (xc + y, yc - x), (xc - y, yc - x),
    ]
    xs, ys = zip(*pts)
    ax.scatter(xs, ys, c="yellow", s=15, zorder=3)


def midpoint_circle(xc, yc, r):
    x, y = 0, r
    p = 1 - r
    pixels = [(x, y)]
    while x < y:
        x += 1
        if p < 0:
            p += 2 * x + 3
        else:
            y -= 1
            p += 2 * (x - y) + 5
        pixels.append((x, y))
    return pixels


def run():
    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("Midpoint Circle Algorithm (Bresenham's Circle)")
    ax.set_xlim(100, 500)
    ax.set_ylim(0, 400)
    ax.set_aspect("equal")
    ax.grid(True, alpha=0.3)

    for r in [50, 100, 150]:
        pixels = midpoint_circle(0, 0, r)
        for x, y in pixels:
            plot_circle_points(ax, 300, 200, x, y)

    ax.text(0.02, 0.98,
            "Midpoint Circle Algorithm (Bresenham's Circle)\n"
            "Concentric circles: r = 50, 100, 150",
            transform=ax.transAxes, fontsize=10, verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="lightcyan", alpha=0.8))

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    run()
```

### Output

![Midpoint Circle Algorithm](assets/05_midpoint_circle.png)

---

## Experiment 6: 2D Translation

**Files:** `exp06_translation.cpp` · `exp06_translation.py`

### Theory

Translation is the simplest geometric transformation — it **moves** every point of an object by the same distance in the same direction.

**Formula:**
```
x' = x + tx
y' = y + ty
```

**Matrix form (homogeneous coordinates):**
```
⎡ x' ⎤   ⎡ 1  0  tx ⎤ ⎡ x ⎤
⎢ y' ⎥ = ⎢ 0  1  ty ⎥ ⎢ y ⎥
⎣ 1  ⎦   ⎣ 0  0  1  ⎦ ⎣ 1 ⎦
```

**To translate an object:** apply the translation to EVERY vertex, then redraw the shape.

**Properties:**
- Preserves shape and size (rigid transformation)
- Preserves orientation
- Lines remain parallel (affine transformation)
- Area is preserved

### Algorithm

```
INPUT: Object vertices V[], Translation vector (tx, ty)
OUTPUT: Translated vertices V'[]

FOR each vertex (x, y) in V:
    x' = x + tx
    y' = y + ty
    ADD (x', y') to V'

DRAW shape using V'
```

### Python Code

```python
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

def draw_triangle(ax, x1, y1, x2, y2, x3, y3, color, label=None):
    triangle = mpatches.Polygon(
        [(x1, y1), (x2, y2), (x3, y3)],
        fill=False, edgecolor=color, linewidth=2, label=label
    )
    ax.add_patch(triangle)


def run():
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

    # ---- Part 1: Translate a LINE ----
    ax1.set_title("2D Translation: Line")
    ax1.set_xlim(0, 420); ax1.set_ylim(0, 300)
    ax1.set_aspect("equal"); ax1.grid(True, alpha=0.3)

    lx1, ly1 = 50, 50
    lx2, ly2 = 200, 150
    tx, ty = 100, 80

    ax1.plot([lx1, lx2], [ly1, ly2], "w-", linewidth=2, label="Original Line")
    ax1.plot([lx1 + tx, lx2 + tx], [ly1 + ty, ly2 + ty],
             "y-", linewidth=2, label=f"Translated (tx={tx}, ty={ty})")
    ax1.scatter([lx1, lx2], [ly1, ly2], c="white", s=40, zorder=4)
    ax1.scatter([lx1 + tx, lx2 + tx], [ly1 + ty, ly2 + ty], c="yellow", s=40, zorder=4)
    ax1.annotate("Original", (lx1, ly1), xytext=(5, 8), textcoords="offset points", color="white", fontsize=8)
    ax1.annotate("Translated", (lx1 + tx, ly1 + ty), xytext=(5, 8), textcoords="offset points", color="yellow", fontsize=8)

    # ---- Part 2: Translate a TRIANGLE ----
    ax2.set_title("2D Translation: Triangle")
    ax2.set_xlim(150, 600); ax2.set_ylim(0, 350)
    ax2.set_aspect("equal"); ax2.grid(True, alpha=0.3)

    x1, y1 = 300, 200
    x2, y2 = 400, 50
    x3, y3 = 200, 50
    ttx, tty = 150, 100

    draw_triangle(ax2, x1, y1, x2, y2, x3, y3, "white", "Original Triangle")
    draw_triangle(ax2, x1 + ttx, y1 + tty, x2 + ttx, y2 + tty,
                  x3 + ttx, y3 + tty, "cyan", f"Translated (tx={ttx}, ty={tty})")
    ax2.scatter([x1, x2, x3], [y1, y2, y3], c="white", s=40, zorder=4)
    ax2.scatter([x1 + ttx, x2 + ttx, x3 + ttx],
                [y1 + tty, y2 + tty, y3 + tty], c="cyan", s=40, zorder=4)
    ax2.annotate("Original", (x1, y1), xytext=(5, 8), textcoords="offset points", color="white", fontsize=8)
    ax2.annotate("Translated", (x1 + ttx, y1 + tty), xytext=(5, 8), textcoords="offset points", color="cyan", fontsize=8)

    for ax in [ax1, ax2]:
        ax.set_xlabel("X"); ax.set_ylabel("Y")
        ax.legend(fontsize=8, loc="lower right")
        ax.set_facecolor("#2b2b2b"); ax.tick_params(colors="white")
        ax.xaxis.label.set_color("white"); ax.yaxis.label.set_color("white")
        ax.title.set_color("white")

    fig.patch.set_facecolor("#2b2b2b")
    plt.tight_layout(); plt.show()

if __name__ == "__main__":
    run()
```

### Output

![2D Translation](assets/06_translation.png)

---

## Experiment 7: 2D Rotation

**Files:** `exp07_rotation.cpp` · `exp07_rotation.py`

### Theory

Rotation turns an object around a fixed point (pivot). Positive angle = counterclockwise.

**Rotation about origin by angle θ:**
```
x' = x·cosθ − y·sinθ
y' = x·sinθ + y·cosθ
```

**Derivation:**
A point (x, y) = (r·cosφ, r·sinφ) after rotation by θ becomes:
```
x' = r·cos(φ+θ) = r·cosφ·cosθ − r·sinφ·sinθ = x·cosθ − y·sinθ
y' = r·sin(φ+θ) = r·sinφ·cosθ + r·cosφ·sinθ = y·cosθ + x·sinθ
```

**Rotation about arbitrary pivot (cx, cy) — 3 steps:**
```
1. Translate pivot to origin:          T(−cx, −cy)
2. Rotate about origin:                R(θ)
3. Translate pivot back:               T(cx, cy)

Combined: P' = T(cx,cy) · R(θ) · T(−cx,−cy) · P
```

In code:
```
x_rel = x − cx
y_rel = y − cy
x' = cx + x_rel·cosθ − y_rel·sinθ
y' = cy + x_rel·sinθ + y_rel·cosθ
```

**Matrix form:**
```
⎡ x' ⎤   ⎡ cosθ  −sinθ  cx(1−cosθ)+cy·sinθ ⎤ ⎡ x ⎤
⎢ y' ⎥ = ⎢ sinθ   cosθ  cy(1−cosθ)−cx·sinθ ⎥ ⎢ y ⎥
⎣ 1  ⎦   ⎣  0      0             1          ⎦ ⎣ 1 ⎦
```

### Algorithm

```
INPUT: Vertex (x, y), Pivot (cx, cy), Angle θ (degrees)
OUTPUT: Rotated vertex (x', y')

1. rad = θ × π / 180
2. cosθ = cos(rad), sinθ = sin(rad)
3. x_rel = x − cx
   y_rel = y − cy
4. x' = cx + x_rel·cosθ − y_rel·sinθ
   y' = cy + x_rel·sinθ + y_rel·cosθ
5. RETURN ROUND(x'), ROUND(y')
```

### Python Code

```python
import math
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

def rotate_point(x, y, cx, cy, angle):
    rad = math.radians(angle)
    cos_a, sin_a = math.cos(rad), math.sin(rad)
    x_rel, y_rel = x - cx, y - cy
    x_rot = x_rel * cos_a - y_rel * sin_a
    y_rot = x_rel * sin_a + y_rel * cos_a
    return round(cx + x_rot), round(cy + y_rot)

def draw_triangle(ax, x1, y1, x2, y2, x3, y3, color, label=None):
    tri = mpatches.Polygon([(x1, y1), (x2, y2), (x3, y3)], fill=False, edgecolor=color, linewidth=2, label=label)
    ax.add_patch(tri)

def run():
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5.5))
    fig.suptitle("2D Rotation Transformation", fontsize=13)

    # Part 1: Rotate a LINE
    ax1.set_title("Rotation: Line")
    ax1.set_xlim(50, 350); ax1.set_ylim(200, 380)
    ax1.set_aspect("equal"); ax1.grid(True, alpha=0.3)

    lx1, ly1, lx2, ly2 = 100, 300, 250, 300
    ax1.plot([lx1, lx2], [ly1, ly2], "w-", linewidth=2, label="Original")
    ax1.scatter([lx1], [ly1], c="red", s=50, zorder=4)

    for deg, color, label in [(45, "yellow", "Rotated 45"), (90, "lime", "Rotated 90")]:
        rx, ry = rotate_point(lx2, ly2, lx1, ly1, deg)
        ax1.plot([lx1, rx], [ly1, ry], color=color, linewidth=2, label=label)
        ax1.scatter([rx], [ry], c=color, s=40, zorder=4)
        ax1.annotate(label, (rx, ry), xytext=(5, 5), textcoords="offset points", color=color, fontsize=8)
    ax1.annotate("Pivot", (lx1, ly1), xytext=(5, 8), textcoords="offset points", color="red", fontsize=8)

    # Part 2: Rotate a TRIANGLE
    ax2.set_title("Rotation: Triangle")
    ax2.set_xlim(200, 600); ax2.set_ylim(0, 350)
    ax2.set_aspect("equal"); ax2.grid(True, alpha=0.3)

    x1, y1, x2, y2, x3, y3 = 400, 80, 500, 200, 300, 200
    cx = (x1 + x2 + x3) // 3; cy = (y1 + y2 + y3) // 3

    draw_triangle(ax2, x1, y1, x2, y2, x3, y3, "white", "Original")
    ax2.scatter([cx], [cy], c="red", s=50, zorder=4)
    ax2.annotate("Centroid", (cx, cy), xytext=(5, 8), textcoords="offset points", color="red", fontsize=8)

    for deg, color, label in [(60, "magenta", "Rotated 60"), (120, "cyan", "Rotated 120")]:
        r = [rotate_point(x1, y1, cx, cy, deg), rotate_point(x2, y2, cx, cy, deg), rotate_point(x3, y3, cx, cy, deg)]
        draw_triangle(ax2, r[0][0], r[0][1], r[1][0], r[1][1], r[2][0], r[2][1], color, label)

    for ax in [ax1, ax2]:
        ax.set_xlabel("X"); ax.set_ylabel("Y")
        ax.legend(fontsize=7, loc="lower right")
        ax.set_facecolor("#2b2b2b"); ax.tick_params(colors="white")
        ax.xaxis.label.set_color("white"); ax.yaxis.label.set_color("white")
        ax.title.set_color("white")

    fig.patch.set_facecolor("#2b2b2b")
    plt.tight_layout(); plt.show()

if __name__ == "__main__":
    run()
```

### Output

![2D Rotation](assets/07_rotation.png)

---

## Experiment 8: 2D Scaling

**Files:** `exp08_scaling.cpp` · `exp08_scaling.py`

### Theory

Scaling changes the **size** of an object. The coordinates are multiplied by scaling factors.

**Scaling about origin:**
```
x' = x × sx
y' = y × sy
```

**Scaling about fixed point (fx, fy) — 3 steps:**
```
1. Translate fixed point to origin:  T(−fx, −fy)
2. Scale about origin:               S(sx, sy)
3. Translate back:                    T(fx, fy)

Combined: P' = T(fx,fy) · S(sx,sy) · T(−fx,−fy) · P
```

In code:
```
x' = fx + (x − fx) × sx
y' = fy + (y − fy) × sy
```

**Matrix form:**
```
⎡ x' ⎤   ⎡ sx  0   fx(1−sx) ⎤ ⎡ x ⎤
⎢ y' ⎥ = ⎢ 0   sy  fy(1−sy) ⎥ ⎢ y ⎥
⎣ 1  ⎦   ⎣ 0   0      1     ⎦ ⎣ 1 ⎦
```

**Uniform vs Differential Scaling:**

| Type | Condition | Effect |
|------|-----------|--------|
| Uniform | sx = sy | Object keeps proportions |
| Differential | sx ≠ sy | Object stretches/distorts |

### Algorithm

```
INPUT: Vertex (x, y), Fixed point (fx, fy), Scaling factors (sx, sy)
OUTPUT: Scaled vertex (x', y')

x' = fx + (x − fx) × sx
y' = fy + (y − fy) × sy
RETURN ROUND(x'), ROUND(y')
```

### Python Code

```python
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

def scale_point(x, y, fx, fy, sx, sy):
    return round(fx + (x - fx) * sx), round(fy + (y - fy) * sy)

def draw_triangle(ax, x1, y1, x2, y2, x3, y3, color, label=None):
    tri = mpatches.Polygon([(x1, y1), (x2, y2), (x3, y3)], fill=False, edgecolor=color, linewidth=2, label=label)
    ax.add_patch(tri)

def run():
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5.5))
    fig.suptitle("2D Scaling Transformation", fontsize=13)

    # Part 1: Scale a RECTANGLE
    ax1.set_title("Scaling: Rectangle")
    ax1.set_xlim(0, 350); ax1.set_ylim(0, 300)
    ax1.set_aspect("equal"); ax1.grid(True, alpha=0.3)

    rx1, ry1, rx2, ry2 = 50, 50, 150, 150
    fx, fy = (rx1 + rx2) // 2, (ry1 + ry2) // 2

    ax1.add_patch(mpatches.Rectangle((rx1, ry1), rx2 - rx1, ry2 - ry1, fill=False, edgecolor="white", linewidth=2, label="Original"))

    for sx, sy, color, label in [
        (1.5, 1.5, "yellow", "Scaled 1.5x (uniform)"),
        (2.0, 0.5, "cyan", "Scaled (2x, 0.5x) (differential)")
    ]:
        p1 = scale_point(rx1, ry1, fx, fy, sx, sy)
        p2 = scale_point(rx2, ry2, fx, fy, sx, sy)
        ax1.add_patch(mpatches.Rectangle(p1, p2[0]-p1[0], p2[1]-p1[1], fill=False, edgecolor=color, linewidth=2, label=label))

    ax1.scatter([fx], [fy], c="red", s=50, zorder=4)
    ax1.annotate("Center", (fx, fy), xytext=(5, 8), textcoords="offset points", color="red", fontsize=8)

    # Part 2: Scale a TRIANGLE
    ax2.set_title("Scaling: Triangle")
    ax2.set_xlim(150, 600); ax2.set_ylim(0, 400)
    ax2.set_aspect("equal"); ax2.grid(True, alpha=0.3)

    x1, y1, x2, y2, x3, y3 = 350, 80, 450, 200, 250, 200
    tfx, tfy = (x1 + x2 + x3) // 3, (y1 + y2 + y3) // 3

    draw_triangle(ax2, x1, y1, x2, y2, x3, y3, "white", "Original")
    p = [scale_point(x1, y1, tfx, tfy, 1.8, 1.8), scale_point(x2, y2, tfx, tfy, 1.8, 1.8), scale_point(x3, y3, tfx, tfy, 1.8, 1.8)]
    draw_triangle(ax2, p[0][0], p[0][1], p[1][0], p[1][1], p[2][0], p[2][1], "magenta", "Scaled 1.8x")
    ax2.scatter([tfx], [tfy], c="red", s=50, zorder=4)
    ax2.annotate("Centroid", (tfx, tfy), xytext=(5, 8), textcoords="offset points", color="red", fontsize=8)

    for ax in [ax1, ax2]:
        ax.set_xlabel("X"); ax.set_ylabel("Y")
        ax.legend(fontsize=7, loc="lower right")
        ax.set_facecolor("#2b2b2b"); ax.tick_params(colors="white")
        ax.xaxis.label.set_color("white"); ax.yaxis.label.set_color("white")
        ax.title.set_color("white")

    fig.patch.set_facecolor("#2b2b2b")
    plt.tight_layout(); plt.show()

if __name__ == "__main__":
    run()
```

### Output

![2D Scaling](assets/08_scaling.png)

---

## Experiment 9: 3D Rotation About Arbitrary Axis

**Files:** `exp09_3d_rotation.cpp` · `exp09_3d_rotation.py`

### Theory

Rotating a 3D object about any line in space (not aligned with x, y, or z axis).

**Rodrigues' Rotation Formula:**
Given a point vector `v` and a unit axis vector `u`, rotation by angle θ:

```
v' = v·cosθ + (u × v)·sinθ + u·(u·v)·(1 − cosθ)
```

| Component | Meaning |
|-----------|---------|
| v·cosθ | Original vector scaled down |
| u × v | Perpendicular component (rotation plane) |
| u·(u·v) | Parallel component (along axis, unchanged) |

**Step-by-step process:**
```
1. Translate so axis passes through origin:  v = P − A₁
2. Normalize axis to unit vector:            u = (A₂ − A₁) / |A₂ − A₁|
3. Apply Rodrigues' formula
4. Translate back:                           P' = v' + A₁
```

**Projection (3D → 2D):**
Oblique projection at 30°:
```
screen_x = world_x + world_z × 0.5 × cos(30°)
screen_y = world_y + world_z × 0.5 × sin(30°)
```

### Python Code

```python
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def rotate_about_axis(point, a1, a2, angle):
    px, py, pz = point[0] - a1[0], point[1] - a1[1], point[2] - a1[2]
    ax, ay, az = a2[0] - a1[0], a2[1] - a1[1], a2[2] - a1[2]
    length = math.sqrt(ax*ax + ay*ay + az*az)
    ux, uy, uz = ax/length, ay/length, az/length

    rad = math.radians(angle)
    cos_a, sin_a = math.cos(rad), math.sin(rad)

    dot = px*ux + py*uy + pz*uz
    cross_x = uy*pz - uz*py
    cross_y = uz*px - ux*pz
    cross_z = ux*py - uy*px

    new_x = px*cos_a + cross_x*sin_a + ux*dot*(1 - cos_a)
    new_y = py*cos_a + cross_y*sin_a + uy*dot*(1 - cos_a)
    new_z = pz*cos_a + cross_z*sin_a + uz*dot*(1 - cos_a)

    return (round(new_x + a1[0]), round(new_y + a1[1]), round(new_z + a1[2]))

def draw_cube_3d(ax, vertices, color):
    edges = [(0,1),(1,2),(2,3),(3,0),(4,5),(5,6),(6,7),(7,4),(0,4),(1,5),(2,6),(3,7)]
    xs, ys, zs = zip(*vertices)
    for i, j in edges:
        ax.plot3D(*zip(vertices[i], vertices[j]), color=color, linewidth=1.5)
    ax.scatter(xs, ys, zs, c=color, s=30)

def run():
    cube = [(250,150,-50),(350,150,-50),(350,250,-50),(250,250,-50),
            (250,150,50),(350,150,50),(350,250,50),(250,250,50)]
    a1, a2 = (260,160,-40), (340,240,40)

    rotated_45 = [rotate_about_axis(v, a1, a2, 45) for v in cube]
    rotated_90 = [rotate_about_axis(v, a1, a2, 90) for v in cube]

    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection="3d")
    ax.set_title("3D Rotation About Arbitrary Axis (Body Diagonal)")

    draw_cube_3d(ax, cube, "white")
    draw_cube_3d(ax, rotated_45, "yellow")
    draw_cube_3d(ax, rotated_90, "cyan")

    ax.text(0.02, 0.98, 0.98, "White = Original | Yellow = 45deg | Cyan = 90deg\nRotation axis = cube body diagonal",
            transform=ax.transAxes, fontsize=10, verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="lightcyan", alpha=0.8))

    ax.set_xlabel("X"); ax.set_ylabel("Y"); ax.set_zlabel("Z")
    ax.set_facecolor("#2b2b2b"); fig.patch.set_facecolor("#2b2b2b")
    ax.xaxis.label.set_color("white"); ax.yaxis.label.set_color("white")
    ax.zaxis.label.set_color("white"); ax.title.set_color("white")
    ax.tick_params(colors="white")
    plt.tight_layout(); plt.show()

if __name__ == "__main__":
    run()
```

### Output

![3D Rotation](assets/09_3d_rotation.png)

---

## Experiment 10: Cohen-Sutherland Line Clipping

**Files:** `exp10_cohen_sutherland.cpp` · `exp10_cohen_sutherland.py`

### Theory

Clips a line against a rectangular window. Each endpoint gets a **4-bit region code** telling where it lies relative to the window.

**Region Code Bits:**
```
Bit 3 (8) = TOP     → y < yMin
Bit 2 (4) = BOTTOM  → y > yMax
Bit 1 (2) = RIGHT   → x > xMax
Bit 0 (1) = LEFT    → x < xMin
```

**Region Layout:**
```
     1001 | 1000 | 1010
    ──────┼──────┼──────
     0001 | 0000 | 0010
    ──────┼──────┼──────
     0101 | 0100 | 0110
```

**Algorithm:**
```
1. Compute codes for both endpoints (code1, code2)
2. IF code1 == 0 AND code2 == 0:
       TRIVIAL ACCEPT — line fully inside, draw it
3. ELSE IF code1 & code2 ≠ 0:
       TRIVIAL REJECT — both on same outside side, discard
4. ELSE:
       Pick outside endpoint
       Clip against the corresponding edge:
         TOP:    x = x₁ + (x₂−x₁)·(yMin−y₁)/(y₂−y₁), y = yMin
         BOTTOM: x = x₁ + (x₂−x₁)·(yMax−y₁)/(y₂−y₁), y = yMax
         LEFT:   y = y₁ + (y₂−y₁)·(xMin−x₁)/(x₂−x₁), x = xMin
         RIGHT:  y = y₁ + (y₂−y₁)·(xMax−x₁)/(x₂−x₁), x = xMax
       Replace outside endpoint with intersection
       Recompute code
       Go to step 2
```

### Python Code

```python
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

INSIDE, LEFT, RIGHT, BOTTOM, TOP = 0, 1, 2, 4, 8
XMIN, YMIN, XMAX, YMAX = 150, 100, 450, 300

def compute_code(x, y):
    code = INSIDE
    if x < XMIN: code |= LEFT
    elif x > XMAX: code |= RIGHT
    if y < YMIN: code |= TOP
    elif y > YMAX: code |= BOTTOM
    return code

def cohen_sutherland_clip(x1, y1, x2, y2):
    code1, code2 = compute_code(x1, y1), compute_code(x2, y2)
    accept = False
    while True:
        if code1 == 0 and code2 == 0:
            accept = True; break
        elif code1 & code2:
            break
        else:
            code_out = code1 if code1 != 0 else code2
            if code_out & TOP:
                x = x1 + (x2 - x1) * (YMIN - y1) / (y2 - y1); y = YMIN
            elif code_out & BOTTOM:
                x = x1 + (x2 - x1) * (YMAX - y1) / (y2 - y1); y = YMAX
            elif code_out & RIGHT:
                y = y1 + (y2 - y1) * (XMAX - x1) / (x2 - x1); x = XMAX
            elif code_out & LEFT:
                y = y1 + (y2 - y1) * (XMIN - x1) / (x2 - x1); x = XMIN
            if code_out == code1:
                x1, y1 = x, y; code1 = compute_code(x1, y1)
            else:
                x2, y2 = x, y; code2 = compute_code(x2, y2)
    if accept:
        return (round(x1), round(y1), round(x2), round(y2))
    return None

def run():
    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("Cohen-Sutherland Line Clipping")
    ax.set_xlim(0, 640); ax.set_ylim(0, 480)
    ax.set_aspect("equal"); ax.grid(True, alpha=0.3)

    ax.add_patch(mpatches.Rectangle((XMIN, YMIN), XMAX-XMIN, YMAX-YMIN, fill=False, edgecolor="white", linewidth=2, label="Clipping Window"))
    ax.text(XMIN+5, YMIN-15, "Clipping Window", color="white", fontsize=8)

    lines = [(50,200,300,80),(500,250,300,350),(100,150,200,250),(50,50,100,80),(500,350,550,400),(200,50,350,50),(500,150,300,200)]
    for x1, y1, x2, y2 in lines:
        ax.plot([x1, x2], [y1, y2], "w-", linewidth=1, alpha=0.4)
    for x1, y1, x2, y2 in lines:
        clipped = cohen_sutherland_clip(x1, y1, x2, y2)
        if clipped:
            ax.plot([clipped[0], clipped[2]], [clipped[1], clipped[3]], "y-", linewidth=2.5)

    ax.text(0.02, 0.98, "White = Original (faded) | Yellow = Visible portion",
            transform=ax.transAxes, fontsize=10, verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="wheat", alpha=0.8))
    ax.set_xlabel("X"); ax.set_ylabel("Y"); ax.legend(fontsize=8, loc="lower right")
    plt.tight_layout(); plt.show()

if __name__ == "__main__":
    run()
```

### Output

![Cohen-Sutherland Line Clipping](assets/10_cohen_sutherland.png)

---

## Experiment 11: Sutherland-Hodgman Polygon Clipping

**Files:** `exp11_sutherland_hodgman.cpp` · `exp11_sutherland_hodgman.py`

### Theory

Clips a polygon against each edge of a rectangular window **sequentially**. The output of one clipping stage becomes the input for the next.

**Clipping order:**
```
1. Clip against LEFT edge   (x = xMin)
2. Clip against RIGHT edge  (x = xMax)
3. Clip against BOTTOM edge (y = yMax)
4. Clip against TOP edge    (y = yMin)
```

**Four cases for each vertex pair (S → P):**

```
       Inside │
      ┌───────┤
      │ ①  ② │  ← S inside, P inside/outside
      │ ③  ④ │  ← S outside, P inside/outside
      └───────┤
      Outside │
```

| Case | S inside | P inside | Output |
|------|----------|----------|--------|
| 1 | ✓ | ✓ | Add P |
| 2 | ✓ | ✗ | Add intersection I |
| 3 | ✗ | ✗ | Add nothing |
| 4 | ✗ | ✓ | Add I, then add P |

**Edge-intersection formulas:**
```
Left   (x = xMin):  y = y₁ + m·(xMin − x₁)
Right  (x = xMax):  y = y₁ + m·(xMax − x₁)
Top    (y = yMin):  x = x₁ + (yMin − y₁) / m
Bottom (y = yMax):  x = x₁ + (yMax − y₁) / m

where m = (y₂ − y₁) / (x₂ − x₁)
```

### Python Code

```python
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

XMIN, YMIN, XMAX, YMAX = 150, 100, 450, 300

def inside(p, edge):
    x, y = p
    if edge == 0: return x >= XMIN
    if edge == 1: return x <= XMAX
    if edge == 2: return y >= YMIN
    if edge == 3: return y <= YMAX
    return False

def intersect(p1, p2, edge):
    x1, y1, x2, y2 = *p1, *p2
    m = (y2 - y1) / (x2 - x1) if x2 != x1 else 1e10
    if edge == 0: return (XMIN, round(y1 + m * (XMIN - x1)))
    if edge == 1: return (XMAX, round(y1 + m * (XMAX - x1)))
    if edge == 2:
        x = round(x1 + (YMIN - y1) / m) if x2 != x1 else x1
        return (x, YMIN)
    if edge == 3:
        x = round(x1 + (YMAX - y1) / m) if x2 != x1 else x1
        return (x, YMAX)
    return (0, 0)

def clip_against_edge(poly, edge):
    if not poly: return []
    result = []
    n = len(poly)
    for i in range(n):
        curr, nxt = poly[i], poly[(i+1)%n]
        ci, ni = inside(curr, edge), inside(nxt, edge)
        if ci and ni: result.append(nxt)
        elif ci and not ni: result.append(intersect(curr, nxt, edge))
        elif not ci and ni:
            result.append(intersect(curr, nxt, edge))
            result.append(nxt)
    return result

def draw_polygon(ax, poly, color, lw=2):
    if len(poly) < 3: return
    xs, ys = zip(*(poly + [poly[0]]))
    ax.plot(xs, ys, color=color, linewidth=lw)

def run():
    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("Sutherland-Hodgman Polygon Clipping")
    ax.set_xlim(0, 640); ax.set_ylim(0, 420)
    ax.set_aspect("equal"); ax.grid(True, alpha=0.3)

    ax.add_patch(mpatches.Rectangle((XMIN,YMIN), XMAX-XMIN, YMAX-YMIN, fill=False, edgecolor="white", linewidth=2, label="Clipping Window"))
    ax.text(XMIN+5, YMIN-15, "Clipping Window", color="white", fontsize=8)

    polygon = [(80,80),(200,50),(350,120),(500,100),(520,250),(400,350),(100,280),(50,200)]
    draw_polygon(ax, polygon, "white", 1.5)

    clipped = polygon[:]
    for edge in range(4):
        clipped = clip_against_edge(clipped, edge)
    draw_polygon(ax, clipped, "yellow", 2.5)

    if clipped:
        cx = sum(p[0] for p in clipped)//len(clipped)
        cy = sum(p[1] for p in clipped)//len(clipped)
        ax.text(cx-20, cy, "Clipped", color="yellow", fontsize=9, fontweight="bold")

    ax.text(0.02, 0.98, "White = Original polygon | Yellow = After clipping",
            transform=ax.transAxes, fontsize=10, verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="wheat", alpha=0.8))
    ax.set_xlabel("X"); ax.set_ylabel("Y"); ax.legend(fontsize=8, loc="lower right")
    plt.tight_layout(); plt.show()

if __name__ == "__main__":
    run()
```

### Output

![Sutherland-Hodgman Polygon Clipping](assets/11_sutherland_hodgman.png)

---

## Experiment 12: Bezier Curve

**Files:** `exp12_bezier.cpp` · `exp12_bezier.py`

### Theory

A Bezier curve uses **control points** to define a smooth curve. The curve passes through the first and last points but only approaches the intermediate ones.

**Cubic Bezier (4 control points):**

```
B(t) = (1−t)³·P₀ + 3t(1−t)²·P₁ + 3t²(1−t)·P₂ + t³·P₃
```

For 0 ≤ t ≤ 1:
- t = 0 → curve starts at P₀
- t = 1 → curve ends at P₃
- Intermediate t values give points "pulled" toward P₁ and P₂

**Bernstein Basis Polynomials:**
```
B₀(t) = (1−t)³      ← weight for P₀
B₁(t) = 3t(1−t)²    ← weight for P₁
B₂(t) = 3t²(1−t)    ← weight for P₂
B₃(t) = t³           ← weight for P₃
```

At each t, B(t) = Σ Pᵢ × Bᵢ(t), so the curve is a **weighted average** of all control points.

**Properties:**
| Property | Description |
|----------|-------------|
| Convex hull | Curve lies inside the convex hull of control points |
| Endpoint interpolation | Passes through P₀ (t=0) and P₃ (t=1) |
| Tangent at start | Direction P₀ → P₁ |
| Tangent at end | Direction P₂ → P₃ |
| Global control | Moving one point changes the **entire** curve |
| Affine invariance | Transform control points = transform the curve |

**de Casteljau's Algorithm (alternative):**
```
Recursively split line segments at parameter t:
1. Connect adjacent control points with lines
2. Find points at t on each line
3. Connect those points
4. Repeat until one point remains → that's B(t)
```

### Python Code

```python
import matplotlib.pyplot as plt
import numpy as np

def bezier_curve(control_x, control_y, steps=100):
    ts = np.linspace(0, 1, steps + 1)
    u = 1 - ts
    b0 = u**3; b1 = 3*ts*u**2; b2 = 3*ts**2*u; b3 = ts**3
    px = b0*control_x[0] + b1*control_x[1] + b2*control_x[2] + b3*control_x[3]
    py = b0*control_y[0] + b1*control_y[1] + b2*control_y[2] + b3*control_y[3]
    return px, py

def draw_control_polygon(ax, x, y):
    ax.plot(x, y, "w--", linewidth=1.5, label="Control polygon")
    ax.scatter(x, y, c="red", s=60, zorder=4)
    for i in range(4):
        ax.annotate(f"P{i}", (x[i], y[i]), xytext=(5,5), textcoords="offset points", color="red", fontsize=9)

def draw_bezier(ax, x, y):
    px, py = bezier_curve(x, y)
    ax.plot(px, py, "y-", linewidth=2.5, label="Bezier curve")

def run():
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))
    fig.suptitle("Bezier Curve (Cubic)", fontsize=13)

    ax1.set_title("Bezier Curve 1 - S Shape")
    ax1.set_xlim(50, 450); ax1.set_ylim(50, 350)
    ax1.set_aspect("equal"); ax1.grid(True, alpha=0.3)
    draw_control_polygon(ax1, [100,200,300,400], [300,100,100,300])
    draw_bezier(ax1, [100,200,300,400], [300,100,100,300])

    ax2.set_title("Bezier Curve 2")
    ax2.set_xlim(50, 550); ax2.set_ylim(200, 450)
    ax2.set_aspect("equal"); ax2.grid(True, alpha=0.3)
    draw_control_polygon(ax2, [100,250,350,500], [400,250,350,400])
    draw_bezier(ax2, [100,250,350,500], [400,250,350,400])

    for ax in [ax1, ax2]:
        ax.set_xlabel("X"); ax.set_ylabel("Y")
        ax.legend(fontsize=8, loc="upper left")
        ax.set_facecolor("#2b2b2b"); ax.tick_params(colors="white")
        ax.xaxis.label.set_color("white"); ax.yaxis.label.set_color("white")
        ax.title.set_color("white")

    fig.patch.set_facecolor("#2b2b2b")
    plt.tight_layout(); plt.show()

if __name__ == "__main__":
    run()
```

### Output

![Bezier Curve](assets/12_bezier.png)

---

## Experiment 13: B-Spline Curve

**Files:** `exp13_b_spline.cpp` · `exp13_b_spline.py`

### Theory

B-Spline (Basis Spline) improves on Bezier by providing **local control** — moving one control point affects only a small region of the curve, not the entire curve.

**Uniform Cubic B-Spline:**

Each segment uses 4 control points (Pᵢ, Pᵢ₊₁, Pᵢ₊₂, Pᵢ₊₃):

```
Bᵢ(t) = (1/6) × [
    (1−t)³·Pᵢ +
    (3t³ − 6t² + 4)·Pᵢ₊₁ +
    (−3t³ + 3t² + 3t + 1)·Pᵢ₊₂ +
    t³·Pᵢ₊₃
]
```

**Matrix form:**
```
Bᵢ(t) = [t³ t² t 1] · (1/6) · M · [Pᵢ Pᵢ₊₁ Pᵢ₊₂ Pᵢ₊₃]ᵀ

       [-1  3 -3  1]
M =    [ 3 -6  3  0]
       [-3  0  3  0]
       [ 1  4  1  0]
```

**Key Properties:**
| Property | Description |
|----------|-------------|
| Local control | Moving Pᵢ affects at most 4 segments |
| Continuity | C² continuous (2nd derivative matches at joins) |
| Endpoints | Does NOT pass through endpoints (unless clamped) |
| Smoothness | Smoother than Bezier at join points |

**Comparison: Bezier vs B-Spline:**

| Property | Bezier | B-Spline |
|----------|--------|----------|
| Control points | n+1 for degree n | n+1 points, any degree k |
| Control type | Global | Local |
| Endpoint interpolation | Yes | No (unless clamped) |
| Continuity at joins | C⁰ or C¹ | C² |
| Complexity | Simpler | More complex |

**Knot Vector:**
Controls the influence range of each control point. For uniform B-spline, knots are evenly spaced: [0, 1, 2, ..., n+4].

### Python Code

```python
import matplotlib.pyplot as plt
import numpy as np

def b_spline_curve(control_x, control_y, steps=50):
    n = len(control_x)
    all_px, all_py = [], []
    for i in range(n - 3):
        ts = np.linspace(0, 1, steps + 1)
        t2 = ts**2; t3 = ts**3
        b0 = (-t3 + 3*t2 - 3*ts + 1)/6.0
        b1 = (3*t3 - 6*t2 + 4)/6.0
        b2 = (-3*t3 + 3*t2 + 3*ts + 1)/6.0
        b3 = t3/6.0
        px = b0*control_x[i] + b1*control_x[i+1] + b2*control_x[i+2] + b3*control_x[i+3]
        py = b0*control_y[i] + b1*control_y[i+1] + b2*control_y[i+2] + b3*control_y[i+3]
        all_px.extend(px); all_py.extend(py)
    return all_px, all_py

def run():
    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("B-Spline Curve (Uniform Cubic)")

    x = [100, 180, 280, 380, 480, 560]
    y = [200, 80, 300, 80, 300, 200]
    px, py = b_spline_curve(x, y)

    ax.plot(px, py, "y-", linewidth=2.5, label="B-Spline curve")
    ax.plot(x, y, "w--", linewidth=1.5, label="Control polygon")
    ax.scatter(x, y, c="red", s=60, zorder=4)
    for i in range(len(x)):
        ax.annotate(f"P{i}", (x[i], y[i]), xytext=(5,5), textcoords="offset points", color="red", fontsize=9)

    ax.text(0.02, 0.98,
            "White = Control polygon | Red = Control points\n"
            "Yellow = B-Spline curve (C^2 continuous, local control)",
            transform=ax.transAxes, fontsize=9, verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="lightcyan", alpha=0.8))

    ax.set_xlabel("X"); ax.set_ylabel("Y")
    ax.legend(fontsize=8, loc="upper right")
    ax.grid(True, alpha=0.3); ax.set_aspect("equal")
    ax.set_facecolor("#2b2b2b"); ax.tick_params(colors="white")
    ax.xaxis.label.set_color("white"); ax.yaxis.label.set_color("white")
    ax.title.set_color("white"); fig.patch.set_facecolor("#2b2b2b")
    plt.tight_layout(); plt.show()

if __name__ == "__main__":
    run()
```

### Output

![B-Spline Curve](assets/13_b_spline.png)

---

## Complete File Reference

| # | Experiment | C++ | Python |
|---|------------|-----|--------|
| 1 | I/O Devices (Theory) | `exp01_io_devices.md` | — |
| 2 | Slope-Intercept Line | `exp02_slope_intercept.cpp` | `exp02_slope_intercept.py` |
| 3 | DDA Line Algorithm | `exp03_dda_line.cpp` | `exp03_dda_line.py` |
| 4 | Bresenham Line Algorithm | `exp04_bresenham_line.cpp` | `exp04_bresenham_line.py` |
| 5 | Midpoint Circle Algorithm | `exp05_midpoint_circle.cpp` | `exp05_midpoint_circle.py` |
| 6 | 2D Translation | `exp06_translation.cpp` | `exp06_translation.py` |
| 7 | 2D Rotation | `exp07_rotation.cpp` | `exp07_rotation.py` |
| 8 | 2D Scaling | `exp08_scaling.cpp` | `exp08_scaling.py` |
| 9 | 3D Rotation About Arbitrary Axis | `exp09_3d_rotation.cpp` | `exp09_3d_rotation.py` |
| 10 | Cohen-Sutherland Line Clipping | `exp10_cohen_sutherland.cpp` | `exp10_cohen_sutherland.py` |
| 11 | Sutherland-Hodgman Polygon Clipping | `exp11_sutherland_hodgman.cpp` | `exp11_sutherland_hodgman.py` |
| 12 | Bezier Curve | `exp12_bezier.cpp` | `exp12_bezier.py` |
| 13 | B-Spline Curve | `exp13_b_spline.cpp` | `exp13_b_spline.py` |

### Utility Files

| File | Purpose |
|------|---------|
| `setup.ps1` | One-time WinBGIm environment setup |
| `menu.ps1` / `menu.bat` | Interactive experiment menu |
| `run.ps1` / `run.bat` | Quick CLI experiment runner |
| `render_all.py` | Regenerate all screenshot images with window frames |
| `frame_screenshot.py` | Add Windows-style window frame to images |
| `include/` | WinBGIm graphics library (headers + lib) |

---

## Quick Reference: Formulas

| Experiment | Key Formula |
|------------|-------------|
| Slope-Intercept | y = m·x + c |
| DDA | x += dx/steps, y += dy/steps |
| Bresenham | p = 2·dy − dx, if p < 0: E else: NE |
| Midpoint Circle | p = 1 − r, if p < 0: E else: SE |
| Translation | x' = x + tx, y' = y + ty |
| Rotation | x' = x·cosθ − y·sinθ, y' = x·sinθ + y·cosθ |
| Scaling | x' = x·sx, y' = y·sy |
| 3D Rotation | v' = v·cosθ + (u×v)·sinθ + u·(u·v)·(1−cosθ) |
| Cohen-Sutherland | 4-bit region codes + edge intersection |
| Sutherland-Hodgman | 4 cases per edge: both in/in→out/out→in/both out |
| Bezier | B(t) = Σ Pᵢ·Bᵢ(t) with Bernstein polynomials |
| B-Spline | Bᵢ(t) = (1/6)·[...] with local cubic basis |
