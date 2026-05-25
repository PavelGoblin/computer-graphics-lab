import matplotlib.pyplot as plt
import matplotlib.patches as mpatches


def scale_point(x, y, fx, fy, sx, sy):
    return round(fx + (x - fx) * sx), round(fy + (y - fy) * sy)


def draw_triangle(ax, x1, y1, x2, y2, x3, y3, color, label=None):
    tri = mpatches.Polygon(
        [(x1, y1), (x2, y2), (x3, y3)],
        fill=False, edgecolor=color, linewidth=2, label=label
    )
    ax.add_patch(tri)


def run():
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5.5))
    fig.suptitle("2D Scaling Transformation", fontsize=13)

    # ---- Part 1: Scale a RECTANGLE ----
    ax1.set_title("Scaling: Rectangle")
    ax1.axhline(0, color='white', linewidth=0.8, alpha=0.3)
    ax1.axvline(0, color='white', linewidth=0.8, alpha=0.3)
    ax1.set_xlim(-50, 350)
    ax1.set_ylim(-50, 280)
    ax1.set_aspect("equal")
    ax1.grid(True, alpha=0.3)

    rx1, ry1 = 50, 50
    rx2, ry2 = 150, 150
    fx = (rx1 + rx2) // 2
    fy = (ry1 + ry2) // 2

    rect_orig = mpatches.Rectangle(
        (rx1, ry1), rx2 - rx1, ry2 - ry1,
        fill=False, edgecolor="white", linewidth=2, label="Original"
    )
    ax1.add_patch(rect_orig)

    for sx, sy, color, label in [
        (1.5, 1.5, "yellow", "Scaled 1.5x (uniform)"),
        (2.0, 0.5, "cyan", "Scaled (2x, 0.5x) (differential)")
    ]:
        p1 = scale_point(rx1, ry1, fx, fy, sx, sy)
        p2 = scale_point(rx2, ry2, fx, fy, sx, sy)
        rect = mpatches.Rectangle(
            p1, p2[0] - p1[0], p2[1] - p1[1],
            fill=False, edgecolor=color, linewidth=2, label=label
        )
        ax1.add_patch(rect)

    ax1.scatter([fx], [fy], c="red", s=50, zorder=4)
    ax1.annotate("Center", (fx, fy), xytext=(5, 8),
                 textcoords="offset points", color="red", fontsize=8)

    # ---- Part 2: Scale a TRIANGLE ----
    ax2.set_title("Scaling: Triangle")
    ax2.axhline(0, color='white', linewidth=0.8, alpha=0.3)
    ax2.axvline(0, color='white', linewidth=0.8, alpha=0.3)
    ax2.set_xlim(-50, 600)
    ax2.set_ylim(-50, 450)
    ax2.set_aspect("equal")
    ax2.grid(True, alpha=0.3)

    x1, y1 = 350, 80
    x2, y2 = 450, 200
    x3, y3 = 250, 200
    tfx = (x1 + x2 + x3) // 3
    tfy = (y1 + y2 + y3) // 3

    draw_triangle(ax2, x1, y1, x2, y2, x3, y3, "white", "Original")

    p = [scale_point(x1, y1, tfx, tfy, 1.8, 1.8),
         scale_point(x2, y2, tfx, tfy, 1.8, 1.8),
         scale_point(x3, y3, tfx, tfy, 1.8, 1.8)]
    draw_triangle(ax2, p[0][0], p[0][1], p[1][0], p[1][1],
                  p[2][0], p[2][1], "magenta", "Scaled 1.8x")

    ax2.scatter([tfx], [tfy], c="red", s=50, zorder=4)
    ax2.annotate("Centroid", (tfx, tfy), xytext=(5, 8),
                 textcoords="offset points", color="red", fontsize=8)

    for ax in [ax1, ax2]:
        ax.set_xlabel("X")
        ax.set_ylabel("Y")
        ax.legend(fontsize=7, loc="lower right")
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
