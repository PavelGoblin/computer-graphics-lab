"""Regenerate all experiment screenshots with window frames."""

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import os

from frame_screenshot import save_framed

DPI = 160

TITLES = {
    "02_slope_intercept": "Exp 02 - Slope-Intercept Line Drawing",
    "03_dda_line":        "Exp 03 - DDA Line Algorithm",
    "04_bresenham_line":  "Exp 04 - Bresenham Line Algorithm",
    "05_midpoint_circle": "Exp 05 - Midpoint Circle Algorithm",
    "06_translation":     "Exp 06 - 2D Translation",
    "07_rotation":        "Exp 07 - 2D Rotation",
    "08_scaling":         "Exp 08 - 2D Scaling",
    "09_3d_rotation":     "Exp 09 - 3D Rotation About Arbitrary Axis",
    "10_cohen_sutherland":"Exp 10 - Cohen-Sutherland Line Clipping",
    "11_sutherland_hodgman":"Exp 11 - Sutherland-Hodgman Polygon Clipping",
    "12_bezier":          "Exp 12 - Bezier Curve",
    "13_b_spline":        "Exp 13 - B-Spline Curve",
}

MODULES = [
    ("exp02_slope_intercept", "02_slope_intercept"),
    ("exp03_dda_line",        "03_dda_line"),
    ("exp04_bresenham_line",  "04_bresenham_line"),
    ("exp05_midpoint_circle", "05_midpoint_circle"),
    ("exp06_translation",     "06_translation"),
    ("exp07_rotation",        "07_rotation"),
    ("exp08_scaling",         "08_scaling"),
    ("exp09_3d_rotation",     "09_3d_rotation"),
    ("exp10_cohen_sutherland","10_cohen_sutherland"),
    ("exp11_sutherland_hodgman","11_sutherland_hodgman"),
    ("exp12_bezier",          "12_bezier"),
    ("exp13_b_spline",        "13_b_spline"),
]

os.makedirs("assets", exist_ok=True)

_orig_show = plt.show

for mod_name, out_name in MODULES:
    plt.close("all")
    raw_path = f"assets/_raw_{out_name}.png"

    def make_saver(fpath, dpi):
        def saver():
            fig = plt.gcf()
            fig.savefig(fpath, dpi=dpi, bbox_inches="tight", facecolor="#0f0f23")
            plt.close(fig)
        return saver

    plt.show = make_saver(raw_path, DPI)

    mod = __import__(mod_name)
    try:
        mod.run()
        framed_path = f"assets/{out_name}.png"
        save_framed(raw_path, TITLES[out_name], framed_path)
        os.remove(raw_path)
        size = os.path.getsize(framed_path)
        print(f"[OK] {out_name}.png  ({size//1024} KB)")
    except Exception as e:
        print(f"[FAIL] {mod_name}: {e}")

plt.show = _orig_show
print("Done — all images rendered with window frames.")
