import matplotlib.pyplot as plt
import numpy as np


def b_spline_curve(control_x, control_y, steps=50):
    n = len(control_x)
    all_px, all_py = [], []

    for i in range(n - 3):
        ts = np.linspace(0, 1, steps + 1)
        t2 = ts ** 2
        t3 = ts ** 3

        b0 = (-t3 + 3*t2 - 3*ts + 1) / 6.0
        b1 = (3*t3 - 6*t2 + 4) / 6.0
        b2 = (-3*t3 + 3*t2 + 3*ts + 1) / 6.0
        b3 = t3 / 6.0

        px = (b0 * control_x[i] + b1 * control_x[i+1]
              + b2 * control_x[i+2] + b3 * control_x[i+3])
        py = (b0 * control_y[i] + b1 * control_y[i+1]
              + b2 * control_y[i+2] + b3 * control_y[i+3])

        all_px.extend(px)
        all_py.extend(py)

    return all_px, all_py


def run():
    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("B-Spline Curve (Uniform Cubic)")
    ax.axhline(0, color='white', linewidth=0.8)
    ax.axvline(0, color='white', linewidth=0.8)
    ax.set_xlim(-50, 600)
    ax.set_ylim(-50, 350)

    x = [100, 180, 280, 380, 480, 560]
    y = [200, 80, 300, 80, 300, 200]

    px, py = b_spline_curve(x, y)
    ax.plot(px, py, "y-", linewidth=2.5, label="B-Spline curve")

    ax.plot(x, y, "w--", linewidth=1.5, label="Control polygon")
    ax.scatter(x, y, c="red", s=60, zorder=4)
    for i in range(len(x)):
        ax.annotate(f"P{i}", (x[i], y[i]), xytext=(5, 5),
                    textcoords="offset points", color="red", fontsize=9)

    ax.text(0.02, 0.98,
            "White = Control polygon | Red = Control points\n"
            "Yellow = B-Spline curve\n"
            "Note: Smooth C^2 continuous curve\n"
            "(does NOT pass through endpoints)",
            transform=ax.transAxes, fontsize=9, verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="lightcyan", alpha=0.8))

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.legend(fontsize=8, loc="upper right")
    ax.grid(True, alpha=0.3)
    ax.set_aspect("equal")
    ax.set_facecolor("#2b2b2b")
    ax.tick_params(colors="white")
    ax.xaxis.label.set_color("white")
    ax.yaxis.label.set_color("white")
    ax.title.set_color("white")
    fig.patch.set_facecolor("#2b2b2b")

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    run()
