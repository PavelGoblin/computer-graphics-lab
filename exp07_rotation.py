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
    tri = mpatches.Polygon(
        [(x1, y1), (x2, y2), (x3, y3)],
        fill=False, edgecolor=color, linewidth=2, label=label
    )
    ax.add_patch(tri)


def run():
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5.5))
    fig.suptitle("2D Rotation Transformation", fontsize=13)

    # ---- Part 1: Rotate a LINE ----
    ax1.set_title("Rotation: Line")
    ax1.set_xlim(50, 350)
    ax1.set_ylim(200, 380)
    ax1.set_aspect("equal")
    ax1.grid(True, alpha=0.3)

    lx1, ly1 = 100, 300
    lx2, ly2 = 250, 300

    ax1.plot([lx1, lx2], [ly1, ly2], "w-", linewidth=2, label="Original")
    ax1.scatter([lx1], [ly1], c="red", s=50, zorder=4)

    for deg, color, label in [(45, "yellow", "Rotated 45"), (90, "lime", "Rotated 90")]:
        rx, ry = rotate_point(lx2, ly2, lx1, ly1, deg)
        ax1.plot([lx1, rx], [ly1, ry], color=color, linewidth=2, label=label)
        ax1.scatter([rx], [ry], c=color, s=40, zorder=4)
        ax1.annotate(label, (rx, ry), xytext=(5, 5),
                     textcoords="offset points", color=color, fontsize=8)

    ax1.annotate("Pivot", (lx1, ly1), xytext=(5, 8),
                 textcoords="offset points", color="red", fontsize=8)

    # ---- Part 2: Rotate a TRIANGLE ----
    ax2.set_title("Rotation: Triangle")
    ax2.set_xlim(200, 600)
    ax2.set_ylim(0, 350)
    ax2.set_aspect("equal")
    ax2.grid(True, alpha=0.3)

    x1, y1 = 400, 80
    x2, y2 = 500, 200
    x3, y3 = 300, 200
    cx = (x1 + x2 + x3) // 3
    cy = (y1 + y2 + y3) // 3

    draw_triangle(ax2, x1, y1, x2, y2, x3, y3, "white", "Original")
    ax2.scatter([cx], [cy], c="red", s=50, zorder=4)
    ax2.annotate("Centroid", (cx, cy), xytext=(5, 8),
                 textcoords="offset points", color="red", fontsize=8)

    for deg, color, label in [(60, "magenta", "Rotated 60"), (120, "cyan", "Rotated 120")]:
        r = [rotate_point(x1, y1, cx, cy, deg),
             rotate_point(x2, y2, cx, cy, deg),
             rotate_point(x3, y3, cx, cy, deg)]
        draw_triangle(ax2, r[0][0], r[0][1], r[1][0], r[1][1],
                      r[2][0], r[2][1], color, label)
        ax2.scatter([r[0][0]], [r[0][1]], c=color, s=30, zorder=4)

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
