# Computer Graphics and Multimedia System Lab (CSE41P8)

All experiments implemented in **C++** (WinBGIm) and **Python** (matplotlib).

---

## Run Commands

```bash
# C++ (requires WinBGIm setup)
.\run.ps1 2        # or .\menu.ps1

# Python (requires matplotlib)
python exp02_slope_intercept.py
```

---

## Experiments

### 1. Input and Output Devices
📄 **Theory only** — [`exp01_io_devices.md`](exp01_io_devices.md)

---

### 2. Line Drawing — Slope-Intercept Formula

**Code:** [`exp02_slope_intercept.py`](exp02_slope_intercept.py) · [`exp02_slope_intercept.cpp`](exp02_slope_intercept.cpp)

**Algorithm:** `y = mx + c` — computes slope `m` and intercept `c`, then iterates over the dominant axis rounding to nearest pixel.

```python
def slope_intercept_line(x1, y1, x2, y2):
    dx, dy = x2 - x1, y2 - y1
    if dx == 0:
        return [(x1, y) for y in range(min(y1,y2), max(y1,y2)+1)]
    m, c = dy/dx, y1 - m*x1
    pixels = []
    if abs(dx) >= abs(dy):
        for x in range(min(x1,x2), max(x1,x2)+1):
            pixels.append((x, round(m*x + c)))
    else:
        for y in range(min(y1,y2), max(y1,y2)+1):
            pixels.append((round((y-c)/m), y))
    return pixels
```

![Slope-Intercept Line](assets/02_slope_intercept.png)

---

### 3. Line Drawing — DDA Algorithm

**Code:** [`exp03_dda_line.py`](exp03_dda_line.py) · [`exp03_dda_line.cpp`](exp03_dda_line.cpp)

**Algorithm:** Digital Differential Analyzer — increments `x` and `y` by fractional steps along the dominant axis, rounding at each step.

```python
def dda_line(x1, y1, x2, y2):
    dx, dy = x2 - x1, y2 - y1
    steps = max(abs(dx), abs(dy))
    x_inc, y_inc = dx/steps, dy/steps
    x, y = float(x1), float(y1)
    pixels = []
    for _ in range(steps + 1):
        pixels.append((round(x), round(y)))
        x += x_inc; y += y_inc
    return pixels
```

![DDA Line Algorithm](assets/03_dda_line.png)

---

### 4. Line Drawing — Bresenham's Algorithm

**Code:** [`exp04_bresenham_line.py`](exp04_bresenham_line.py) · [`exp04_bresenham_line.cpp`](exp04_bresenham_line.cpp)

**Algorithm:** Integer-only arithmetic using a decision parameter — no floating point, no rounding.

```python
def bresenham_line(x1, y1, x2, y2):
    dx, dy = abs(x2-x1), abs(y2-y1)
    sx, sy = (1 if x1<x2 else -1), (1 if y1<y2 else -1)
    swapped = 0
    if dy > dx:
        dx, dy = dy, dx; swapped = 1
    p, x, y = 2*dy - dx, x1, y1
    pixels = []
    for _ in range(dx + 1):
        pixels.append((x, y))
        while p >= 0:
            if swapped: x += sx
            else: y += sy
            p -= 2*dx
        if swapped: y += sy
        else: x += sx
        p += 2*dy
    return pixels
```

![Bresenham Line Algorithm](assets/04_bresenham_line.png)

---

### 5. Midpoint Circle Algorithm

**Code:** [`exp05_midpoint_circle.py`](exp05_midpoint_circle.py) · [`exp05_midpoint_circle.cpp`](exp05_midpoint_circle.cpp)

**Algorithm:** Uses 8-way symmetry and a decision parameter — only computes 1/8 of the circle.

```python
def midpoint_circle(xc, yc, r):
    x, y, p = 0, r, 1 - r
    pixels = [(x, y)]
    while x < y:
        x += 1
        if p < 0: p += 2*x + 3
        else: y -= 1; p += 2*(x - y) + 5
        pixels.append((x, y))
    return pixels
```

![Midpoint Circle Algorithm](assets/05_midpoint_circle.png)

---

### 6. 2D Translation

**Code:** [`exp06_translation.py`](exp06_translation.py) · [`exp06_translation.cpp`](exp06_translation.cpp)

**Formula:** `x' = x + tx, y' = y + ty` — moves every vertex by the same offset.

![2D Translation](assets/06_translation.png)

---

### 7. 2D Rotation

**Code:** [`exp07_rotation.py`](exp07_rotation.py) · [`exp07_rotation.cpp`](exp07_rotation.cpp)

**Formula:** `x' = cx + (x-cx)·cosθ - (y-cy)·sinθ`, `y' = cy + (x-cx)·sinθ + (y-cy)·cosθ`

![2D Rotation](assets/07_rotation.png)

---

### 8. 2D Scaling

**Code:** [`exp08_scaling.py`](exp08_scaling.py) · [`exp08_scaling.cpp`](exp08_scaling.cpp)

**Formula:** `x' = fx + (x-fx)·sx, y' = fy + (y-fy)·sy` — uniform and differential scaling.

![2D Scaling](assets/08_scaling.png)

---

### 9. 3D Rotation About Arbitrary Axis

**Code:** [`exp09_3d_rotation.py`](exp09_3d_rotation.py) · [`exp09_3d_rotation.cpp`](exp09_3d_rotation.cpp)

**Algorithm:** Rodrigues' rotation formula `v' = v·cosθ + (u×v)·sinθ + u·(u·v)·(1-cosθ)`

![3D Rotation](assets/09_3d_rotation.png)

---

### 10. Cohen-Sutherland Line Clipping

**Code:** [`exp10_cohen_sutherland.py`](exp10_cohen_sutherland.py) · [`exp10_cohen_sutherland.cpp`](exp10_cohen_sutherland.cpp)

**Algorithm:** 4-bit region codes to classify endpoints; trivial accept/reject or clip against window edges.

![Cohen-Sutherland Line Clipping](assets/10_cohen_sutherland.png)

---

### 11. Sutherland-Hodgman Polygon Clipping

**Code:** [`exp11_sutherland_hodgman.py`](exp11_sutherland_hodgman.py) · [`exp11_sutherland_hodgman.cpp`](exp11_sutherland_hodgman.cpp)

**Algorithm:** Clip polygon sequentially against left, right, bottom, top edges using 4 cases per vertex pair.

![Sutherland-Hodgman Polygon Clipping](assets/11_sutherland_hodgman.png)

---

### 12. Bezier Curve

**Code:** [`exp12_bezier.py`](exp12_bezier.py) · [`exp12_bezier.cpp`](exp12_bezier.cpp)

**Formula (Cubic):** `B(t) = (1-t)³·P₀ + 3t(1-t)²·P₁ + 3t²(1-t)·P₂ + t³·P₃`

![Bezier Curve](assets/12_bezier.png)

---

### 13. B-Spline Curve

**Code:** [`exp13_b_spline.py`](exp13_b_spline.py) · [`exp13_b_spline.cpp`](exp13_b_spline.cpp)

**Properties:** Local control, C² continuity, uniform cubic basis functions.

![B-Spline Curve](assets/13_b_spline.png)

---

## File Reference

| # | C++ | Python | Description |
|---|-----|--------|-------------|
| 1 | — | — | I/O Devices (theory) |
| 2 | `exp02_slope_intercept.cpp` | `exp02_slope_intercept.py` | Slope-Intercept Line |
| 3 | `exp03_dda_line.cpp` | `exp03_dda_line.py` | DDA Line |
| 4 | `exp04_bresenham_line.cpp` | `exp04_bresenham_line.py` | Bresenham Line |
| 5 | `exp05_midpoint_circle.cpp` | `exp05_midpoint_circle.py` | Midpoint Circle |
| 6 | `exp06_translation.cpp` | `exp06_translation.py` | 2D Translation |
| 7 | `exp07_rotation.cpp` | `exp07_rotation.py` | 2D Rotation |
| 8 | `exp08_scaling.cpp` | `exp08_scaling.py` | 2D Scaling |
| 9 | `exp09_3d_rotation.cpp` | `exp09_3d_rotation.py` | 3D Rotation |
| 10 | `exp10_cohen_sutherland.cpp` | `exp10_cohen_sutherland.py` | Cohen-Sutherland Clipping |
| 11 | `exp11_sutherland_hodgman.cpp` | `exp11_sutherland_hodgman.py` | Sutherland-Hodgman Clipping |
| 12 | `exp12_bezier.cpp` | `exp12_bezier.py` | Bezier Curve |
| 13 | `exp13_b_spline.cpp` | `exp13_b_spline.py` | B-Spline Curve |
