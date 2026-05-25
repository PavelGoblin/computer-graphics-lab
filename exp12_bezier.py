import matplotlib.pyplot as plt
import numpy as np


def bezier_curve(control_x, control_y, steps=100):
    ts = np.linspace(0, 1, steps + 1)
    u = 1 - ts
    b0 = u ** 3
    b1 = 3 * ts * u ** 2
    b2 = 3 * ts ** 2 * u
    b3 = ts ** 3

    px = (b0 * control_x[0] + b1 * control_x[1]
          + b2 * control_x[2] + b3 * control_x[3])
    py = (b0 * control_y[0] + b1 * control_y[1]
          + b2 * control_y[2] + b3 * control_y[3])
    return px, py


def draw_control_polygon(ax, x, y, color="white"):
    ax.plot(x, y, color=color, linewidth=1.5, linestyle="--", label="Control polygon")
    ax.scatter(x, y, c="red", s=60, zorder=4)
    for i in range(4):
        ax.annotate(f"P{i}", (x[i], y[i]), xytext=(5, 5),
                    textcoords="offset points", color="red", fontsize=9)


def draw_bezier(ax, x, y, color="yellow"):
    px, py = bezier_curve(x, y)
    ax.plot(px, py, color=color, linewidth=2.5, label="Bezier curve")


def run():
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))
    fig.suptitle("Bezier Curve (Cubic)", fontsize=13)

    # Curve 1
    ax1.set_title("Bezier Curve 1 - S Shape")
    ax1.axhline(0, color='white', linewidth=0.8, alpha=0.3)
    ax1.axvline(0, color='white', linewidth=0.8, alpha=0.3)
    ax1.set_xlim(-50, 450)
    ax1.set_ylim(-50, 400)
    ax1.set_aspect("equal")
    ax1.grid(True, alpha=0.3)

    x1 = [100, 200, 300, 400]
    y1 = [300, 100, 100, 300]
    draw_control_polygon(ax1, x1, y1)
    draw_bezier(ax1, x1, y1)

    # Curve 2
    ax2.set_title("Bezier Curve 2")
    ax2.axhline(0, color='white', linewidth=0.8, alpha=0.3)
    ax2.axvline(0, color='white', linewidth=0.8, alpha=0.3)
    ax2.set_xlim(-50, 550)
    ax2.set_ylim(-50, 500)
    ax2.set_aspect("equal")
    ax2.grid(True, alpha=0.3)

    x2 = [100, 250, 350, 500]
    y2 = [400, 250, 350, 400]
    draw_control_polygon(ax2, x2, y2)
    draw_bezier(ax2, x2, y2)

    for ax in [ax1, ax2]:
        ax.set_xlabel("X")
        ax.set_ylabel("Y")
        ax.legend(fontsize=8, loc="upper left")
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
