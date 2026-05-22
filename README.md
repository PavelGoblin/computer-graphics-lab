# Computer Graphics and Multimedia System Lab (CSE41P8)

## ⚡ QUICK START (3 ways to run)

### 🎮 Method 1 — Interactive Menu (easiest!)
```
Double-click: menu.bat
```
Then pick any experiment from 1-13 and press Enter.

### ⌨ Method 2 — Command Line
```batch
run 5     → Runs experiment 5 (Midpoint Circle)
run 10    → Runs experiment 10 (Cohen-Sutherland)
```

### 🖥 Method 3 — PowerShell
```powershell
.\menu.ps1          # Same interactive menu
.\run.ps1 3         # Run experiment 3 directly
```

---

## 🔧 ONE-TIME SETUP

### Step 1: Install MinGW GCC (if not already installed)
Check if you have it:
```cmd
g++ --version
```
If not, install via:
```powershell
winget install -e --id MSYS2.MSYS2
```
Then open **MSYS2 UCRT64** terminal and run:
```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```
Add `C:\msys64\ucrt64\bin` to your System PATH.

### Step 2: Run Setup
```powershell
.\setup.ps1
```
This copies the WinBGIm headers and checks everything is ready.

---

## 📂 WHAT'S INSIDE

| File | What it does |
|------|-------------|
| `menu.bat` / `menu.ps1` | Interactive lab menu |
| `run.bat` | Quick CLI runner |
| `run.ps1` | PowerShell quick runner |
| `setup.ps1` | One-time environment setup |
| `exp01_io_devices.md` | **Theory:** Input & Output devices |
| `exp02_*.cpp` – `exp13_*.cpp` | **Code** for all 12 programming experiments |
| `include/` | WinBGIm graphics library (headers + lib) |
| `README.md` | Full theory for all 13 experiments |

---

# Theory: All 13 Experiments

---

## Experiment 1: Input and Output Devices

### Input Devices
| Device | Description | Types |
|--------|-------------|-------|
| **Keyboard** | Alphanumeric input using keys | QWERTY, AZERTY, virtual |
| **Mouse** | Pointing device for GUI interaction | Mechanical, optical, laser, wireless |
| **Touchscreen** | Direct touch input on display | Resistive, capacitive, infrared |
| **Scanner** | Converts physical documents to digital | Flatbed, sheet-fed, drum, handheld |
| **Digitizer** | Converts analog coordinates to digital | Graphics tablet, digitizing tablet |
| **Light Pen** | Points directly at screen (CRT era) | — |
| **Joystick** | 2D/3D positional control | Analog, digital, gamepad |
| **Trackball** | Stationary ball for cursor control | — |
| **Microphone** | Audio input for voice/speech | — |
| **Camera** | Captures images/video | Webcam, DSLR, CCTV |
| **Barcode Reader** | Scans barcodes | Laser, CCD, camera-based |
| **Biometric Scanner** | Fingerprint, retina, face recognition | — |

### Output Devices
| Device | Description | Types |
|--------|-------------|-------|
| **Monitor (CRT)** | Cathode Ray Tube — electron beam on phosphor | Raster scan, vector scan |
| **Monitor (LCD)** | Liquid Crystal Display — backlit crystals | TN, IPS, VA, OLED, AMOLED |
| **Monitor (LED)** | Light Emitting Diode — individual LEDs | MicroLED, MiniLED |
| **Printer** | Hardcopy output on paper | Impact (dot matrix), Non-impact (inkjet, laser, thermal) |
| **Plotter** | Large-format vector drawing | Drum, flatbed, inkjet plotter |
| **Projector** | Projects computer output onto large screen | DLP, LCD, LCoS |
| **Speaker/Headphones** | Audio output | Stereo, surround sound, studio monitors |
| **VR/AR Headset** | Immersive 3D display | HTC Vive, Oculus Rift, HoloLens |

### Hardcopy vs Softcopy
| Aspect | Hardcopy | Softcopy |
|--------|----------|----------|
| Medium | Paper, film | Screen, projector |
| Permanent | Yes | No (volatile) |
| Portable | Physically | Digitally |
| Devices | Printer, plotter | Monitor, projector |

---

## Experiment 2: Line Using Slope-Intercept Formula

### Theory
The slope-intercept form of a line is: **y = mx + c**

Where:
- **m** = slope of the line = (y₂ - y₁) / (x₂ - x₁)
- **c** = y-intercept = y₁ - m × x₁

### Algorithm
1. Input two endpoints (x₁, y₁) and (x₂, y₂)
2. Compute m = (y₂ - y₁) / (x₂ - x₁)
3. Compute c = y₁ - m × x₁
4. If |dx| > |dy|, iterate x from x₁ to x₂:
   - y = round(m × x + c)
   - putpixel(x, y)
5. Else, iterate y from y₁ to y₂:
   - x = round((y - c) / m)
   - putpixel(x, y)

### Limitations
- Floating-point arithmetic (slow on older hardware)
- Vertical lines have infinite slope (divide-by-zero)
- Repeated floating-point multiplication accumulates error
- Rounding errors visible on long lines

### Example
Points: (2, 3) and (8, 11)
- m = (11-3)/(8-2) = 8/6 = 1.333
- c = 3 - 1.333×2 = 3 - 2.666 = 0.334
- x=2 → y=3, x=3 → y=4, x=4 → y=6, x=5 → y=7, x=6 → y=8, x=7 → y=10, x=8 → y=11

---

## Experiment 3: DDA (Digital Differential Analyzer) Line Algorithm

### Theory
DDA is an incremental scan-conversion algorithm. Instead of computing y from mx+c at each step (which requires multiplication), DDA adds a small increment to the previous value.

### Algorithm
1. Input endpoints (x₁, y₁) and (x₂, y₂)
2. Compute dx = x₂ - x₁, dy = y₂ - y₁
3. steps = max(|dx|, |dy|)
4. x_inc = dx / steps, y_inc = dy / steps
5. x = x₁, y = y₁
6. For i = 0 to steps:
   - putpixel(round(x), round(y))
   - x += x_inc, y += y_inc

### Why steps = max(|dx|, |dy|)?
This ensures we take one step per pixel along the dominant axis. If dx is larger, we step along x; if dy is larger, we step along y.

### Advantages
- Simple and easy to implement
- No integer overflow (handles large coordinates)
- Works for any slope including vertical/horizontal

### Disadvantages
- Floating-point arithmetic (rounding errors)
- Rounding operation required at each step
- Slower than integer-only algorithms

### Example
Points: (3, 2) to (9, 7)
- dx = 6, dy = 5, steps = 6
- x_inc = 1.0, y_inc = 0.833
- (3,2) → (4,3) → (5,3) → (6,4) → (7,5) → (8,6) → (9,7)

---

## Experiment 4: Bresenham's Line Algorithm

### Theory
Bresenham's algorithm uses only integer arithmetic — no floating-point, no rounding. It selects the optimal pixel at each step using a **decision parameter** that tracks the error.

For lines with slope 0 < m < 1 (dx > dy):

**Decision Parameter:**
- p₀ = 2dy - dx
- If pᵢ < 0: pᵢ₊₁ = pᵢ + 2dy (plot E)
- If pᵢ ≥ 0: pᵢ₊₁ = pᵢ + 2dy - 2dx (plot NE)

### Algorithm (Octant 1: |dx| > |dy|, dx > 0)
1. Input (x₁, y₁), (x₂, y₂)
2. dx = |x₂ - x₁|, dy = |y₂ - y₁|
3. p = 2×dy - dx
4. For each x from x₁ to x₂:
   - putpixel(x, y)
   - If p < 0: p += 2×dy
   - Else: y += sign(dy), p += 2×(dy - dx)

### Generalization to All Octants
The algorithm works in all octants by considering:
- Step direction (increase or decrease x/y)
- Which axis is the driving axis (swap x/y if |dy| > |dx|)

### Advantages
- Integer arithmetic only (fast)
- No division, no rounding
- Produces exact results
- Easily adapted to hardware

### Example
Points: (2, 2) to (8, 5)
- dx = 6, dy = 3, p₀ = 2×3 - 6 = 0
- Plot (2,2), p=0 → y++, p += 2(3-6) = -6
- Plot (3,3), p=-6 → p += 2×3 = 0
- Plot (4,3), p=0 → y++, p += 2(3-6) = -6
- Plot (5,4), p=-6 → p += 2×3 = 0
- Plot (6,4), p=0 → y++, p += 2(3-6) = -6
- Plot (7,5), p=-6 → p += 2×3 = 0
- Plot (8,5)

---

## Experiment 5: Midpoint Circle Algorithm

### Theory
The midpoint (or Bresenham's) circle algorithm uses the implicit equation: **f(x, y) = x² + y² - r² = 0**

- f(x, y) < 0 → point inside circle
- f(x, y) = 0 → point on circle
- f(x, y) > 0 → point outside circle

Using **8-way symmetry**: if (x, y) is on the circle, so are (±x, ±y) and (±y, ±x). We only compute 1/8 of the circle and reflect.

### Decision Parameter
Starting at (0, r):
- p₀ = 5/4 - r (or 1 - r for integer arithmetic)
- At each step x → x + 1:
  - If p < 0 (E pixel): p += 2x + 3, y unchanged
  - If p ≥ 0 (SE pixel): p += 2(x - y) + 5, y -= 1

### Algorithm
1. Input center (xc, yc) and radius r
2. x = 0, y = r, p = 1 - r
3. While x ≤ y:
   - Plot 8 symmetric points
   - If p < 0: p += 2×x + 3
   - Else: y--, p += 2×(x - y) + 5
   - x++

### Example
r = 10, center (0,0):
- p₀ = 1 - 10 = -9
- x=0, y=10, p=-9 → p+=3 = -6 → plot 8 points
- x=1, y=10, p=-6 → p+=5 = -1 → plot
- x=2, y=10, p=-1 → p+=7 = 6 → plot
- x=3, y=10, p=6 → y--, p+=2(3-10)+5 = -9 → plot
- ... continues until x > y

---

## Experiment 6: 2D Translation

### Theory
Translation moves an object by adding translation vectors to all points.

**Matrix form:**
```
⎡ x' ⎤   ⎡ x ⎤   ⎡ tx ⎤
⎢ y' ⎥ = ⎢ y ⎥ + ⎢ ty ⎥
⎣ 1  ⎦   ⎣ 1 ⎦   ⎣ 1  ⎦
```

Or in homogeneous coordinates:
```
⎡ x' ⎤   ⎡ 1 0 tx ⎤ ⎡ x ⎤
⎢ y' ⎥ = ⎢ 0 1 ty ⎥ ⎢ y ⎥
⎣ 1  ⎦   ⎣ 0 0 1  ⎦ ⎣ 1 ⎦
```

### Algorithm
For each vertex (x, y) of the object:
- x' = x + tx
- y' = y + ty
- Redraw object at new coordinates

---

## Experiment 7: 2D Rotation

### Theory
Rotation about the origin by angle θ (counterclockwise):

```
x' = x·cos(θ) - y·sin(θ)
y' = x·sin(θ) + y·cos(θ)
```

**Matrix form:**
```
⎡ x' ⎤   ⎡ cos θ  -sin θ  0 ⎤ ⎡ x ⎤
⎢ y' ⎥ = ⎢ sin θ   cos θ  0 ⎥ ⎢ y ⎥
⎣ 1  ⎦   ⎣   0       0    1 ⎦ ⎣ 1 ⎦
```

### Rotation About an Arbitrary Point (xr, yr)
1. Translate object so (xr, yr) → origin: T(-xr, -yr)
2. Rotate about origin: R(θ)
3. Translate back: T(xr, yr)

Composite: **P' = T(xr, yr) · R(θ) · T(-xr, -yr) · P**

---

## Experiment 8: 2D Scaling

### Theory
Scaling changes the size of an object by multiplying coordinates by scaling factors.

```
x' = x × sx
y' = y × sy
```

**Matrix form:**
```
⎡ x' ⎤   ⎡ sx  0   0 ⎤ ⎡ x ⎤
⎢ y' ⎥ = ⎢ 0   sy  0 ⎥ ⎢ y ⎥
⎣ 1  ⎦   ⎣ 0   0   1 ⎦ ⎣ 1 ⎦
```

### Scaling About a Fixed Point (xf, yf)
1. Translate fixed point to origin: T(-xf, -yf)
2. Scale: S(sx, sy)
3. Translate back: T(xf, yf)

**P' = T(xf, yf) · S(sx, sy) · T(-xf, -yf) · P**

### Uniform vs Differential Scaling
- **Uniform**: sx = sy (proportional scaling)
- **Differential**: sx ≠ sy (distorts proportions)

---

## Experiment 9: 3D Rotation About an Arbitrary Axis

### Theory
Rotating a 3D object about any line in space (not aligned with x, y, or z axis).

### Steps (using the translation-rotation approach):
1. **Translate** the axis so it passes through the origin
2. **Rotate** the axis to align with the Z-axis:
   - Rotate about X-axis by angle α to align with XZ-plane
   - Rotate about Y-axis by angle β to align with Z-axis
3. **Rotate** about Z-axis by desired angle θ
4. **Inverse rotate** to restore axis orientation
5. **Inverse translate** to restore axis position

### Mathematical Details
Let the axis be defined by a direction vector V = (a, b, c) passing through point P₀.

**Step 1:** Translate by (-P₀)

**Step 2a:** Rotate about X-axis by α:
```
cos α = c / √(b² + c²)
sin α = b / √(b² + c²)
```

**Step 2b:** Rotate about Y-axis by β:
```
cos β = √(b² + c²) / |V|
sin β = a / |V|   (with sign)
```

**Step 3:** Rotate about Z-axis by θ:
```
x' = x·cos θ - y·sin θ
y' = x·sin θ + y·cos θ
z' = z
```

**Complete composite matrix:**
R = T(P₀) · Rx⁻¹(α) · Ry⁻¹(β) · Rz(θ) · Ry(β) · Rx(α) · T(-P₀)

### Rodrigues' Rotation Formula (Alternative)
For rotation by angle θ about unit vector u = (ux, uy, uz):
```
v' = v·cosθ + (u × v)·sinθ + u·(u·v)·(1-cosθ)
```

---

## Experiment 10: Cohen-Sutherland Line Clipping

### Theory
Efficiently clips a line against a rectangular clipping window by assigning **region codes** to endpoints.

### 4-bit Region Codes
```
  1001 | 1000 | 1010
  ─────┼──────┼─────
  0001 | 0000 | 0010
  ─────┼──────┼─────
  0101 | 0100 | 0110
```

Bit 3 (8): TOP (y > ymax)
Bit 2 (4): BOTTOM (y < ymin)
Bit 1 (2): RIGHT (x > xmax)
Bit 0 (1): LEFT (x < xmin)

### Algorithm
1. Compute region codes for both endpoints (code1, code2)
2. **Trivial accept**: code1 == 0 AND code2 == 0 (both inside)
3. **Trivial reject**: code1 AND code2 ≠ 0 (both on same outside side)
4. **Otherwise**: clip against an edge where a non-zero bit exists:
   - Choose an endpoint with non-zero code
   - Compute intersection with the corresponding edge
   - Replace that endpoint with intersection point
   - Repeat until trivial accept or reject

### Intersection Formulas
- **Left** (x = xmin): y = y₁ + m·(xmin - x₁)
- **Right** (x = xmax): y = y₁ + m·(xmax - x₁)
- **Bottom** (y = ymin): x = x₁ + (ymin - y₁)/m
- **Top** (y = ymax): x = x₁ + (ymax - y₁)/m

Where m = (y₂ - y₁) / (x₂ - x₁)

---

## Experiment 11: Sutherland-Hodgman Polygon Clipping

### Theory
Clips a convex or concave polygon against each edge of a rectangular clipping window sequentially.

### The Four Clipping Stages
The polygon is processed against each clipping edge in order:
1. Clip against **Left** edge (x = xmin)
2. Clip against **Right** edge (x = xmax)
3. Clip against **Bottom** edge (y = ymin)
4. Clip against **Top** edge (y = ymax)

Output of each stage becomes input for the next.

### Point Classification (per edge)
For each pair of consecutive vertices (current S, next P):
- **Case 1 (S inside, P inside)**: Output P
- **Case 2 (S inside, P outside)**: Output intersection I
- **Case 3 (S outside, P outside)**: Output nothing
- **Case 4 (S outside, P inside)**: Output intersection I, then P

### Edge-Intersection Formula
For clipping against edge x = k:
- y = y₁ + m·(k - x₁)

For clipping against edge y = k:
- x = x₁ + (k - y₁)/m

---

## Experiment 12: Bezier Curves

### Theory
A Bezier curve is defined by a set of **control points**. The curve passes through the first and last control points but generally does not pass through intermediate ones (they "pull" the curve).

### Cubic Bezier Curve (4 control points)
**Parametric equation** (0 ≤ t ≤ 1):
```
B(t) = (1-t)³·P₀ + 3t(1-t)²·P₁ + 3t²(1-t)·P₂ + t³·P₃
```

**Bernstein basis polynomials:**
- B₀₃(t) = (1-t)³       — weight for P₀
- B₁₃(t) = 3t(1-t)²     — weight for P₁
- B₂₃(t) = 3t²(1-t)     — weight for P₂
- B₃₃(t) = t³            — weight for P₃

### de Casteljau's Algorithm (Alternative)
Recursive linear interpolation:
1. Connect adjacent control points with lines
2. Find points at parameter t on each line
3. Connect those points with lines
4. Repeat until one point remains → that's B(t)

### Properties
- Curve lies within **convex hull** of control points
- **Endpoint interpolation**: passes through P₀ and P₃
- **Tangent at P₀**: direction P₁-P₀
- **Tangent at P₃**: direction P₃-P₂
- **Affine invariance**: transforming control points = transforming the curve

---

## Experiment 13: B-Spline Curve

### Theory
B-Spline (Basis Spline) curves use basis functions that provide **local control** — moving one control point affects only a local region of the curve, unlike Bezier curves where all control points influence the entire curve.

### Uniform Cubic B-Spline (4 control points per segment)
For segment i (using control points Pᵢ, Pᵢ₊₁, Pᵢ₊₂, Pᵢ₊₃):

```
Bᵢ(t) = (1/6) × [
    (1-t)³·Pᵢ +
    (3t³ - 6t² + 4)·Pᵢ₊₁ +
    (-3t³ + 3t² + 3t + 1)·Pᵢ₊₂ +
    t³·Pᵢ₊₃
]
```

**Matrix form:**
```
Bᵢ(t) = [t³ t² t 1] · (1/6) · ⎡ -1  3 -3  1 ⎤ ⎡ Pᵢ   ⎤
                              ⎢  3 -6  3  0 ⎥ ⎢ Pᵢ₊₁ ⎥
                              ⎢ -3  0  3  0 ⎥ ⎢ Pᵢ₊₂ ⎥
                              ⎣  1  4  1  0 ⎦ ⎣ Pᵢ₊₃ ⎦
```

### Key Properties
- **Local control**: Changing Pᵢ affects at most 4 segments
- **Continuity**: C² continuous (second derivative continuous)
- **No endpoint interpolation**: Curve does not pass through endpoints (unless clamped)
- **Smoother** than Bezier at join points

### Knot Vector
Controls the influence range of each control point. For uniform B-spline, knots are evenly spaced: [0, 1, 2, ..., n+4].

### Types
| Type | Description |
|------|-------------|
| **Uniform** | Equal knot spacing |
| **Non-uniform** | Unequal knot spacing |
| **Open (Clamped)** | First/last knots repeated k+1 times (curve passes through endpoints) |
| **Closed (Periodic)** | Wraps around (smooth closed curve) |
