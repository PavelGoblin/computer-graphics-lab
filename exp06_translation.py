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
    ax1.axhline(0, color='white', linewidth=0.8, alpha=0.3)
    ax1.axvline(0, color='white', linewidth=0.8, alpha=0.3)
    ax1.set_xlim(-50, 350)
    ax1.set_ylim(-50, 280)
    ax1.set_aspect("equal")
    ax1.grid(True, alpha=0.3)

    lx1, ly1 = 50, 50
    lx2, ly2 = 200, 150
    tx, ty = 100, 80

    ax1.plot([lx1, lx2], [ly1, ly2], "w-", linewidth=2, label="Original Line")
    ax1.plot([lx1 + tx, lx2 + tx], [ly1 + ty, ly2 + ty],
             "y-", linewidth=2, label=f"Translated (tx={tx}, ty={ty})")

    ax1.scatter([lx1, lx2], [ly1, ly2], c="white", s=40, zorder=4)
    ax1.scatter([lx1 + tx, lx2 + tx], [ly1 + ty, ly2 + ty],
                c="yellow", s=40, zorder=4)

    ax1.annotate("Original", (lx1, ly1), xytext=(5, 8),
                 textcoords="offset points", color="white", fontsize=8)
    ax1.annotate("Translated", (lx1 + tx, ly1 + ty), xytext=(5, 8),
                 textcoords="offset points", color="yellow", fontsize=8)

    # ---- Part 2: Translate a TRIANGLE ----
    ax2.set_title("2D Translation: Triangle")
    ax2.axhline(0, color='white', linewidth=0.8, alpha=0.3)
    ax2.axvline(0, color='white', linewidth=0.8, alpha=0.3)
    ax2.set_xlim(-50, 600)
    ax2.set_ylim(-50, 350)
    ax2.set_aspect("equal")
    ax2.grid(True, alpha=0.3)

    x1, y1 = 300, 200
    x2, y2 = 400, 50
    x3, y3 = 200, 50
    ttx, tty = 150, 100

    draw_triangle(ax2, x1, y1, x2, y2, x3, y3, "white", "Original Triangle")
    draw_triangle(ax2, x1 + ttx, y1 + tty, x2 + ttx, y2 + tty,
                  x3 + ttx, y3 + tty, "cyan",
                  f"Translated (tx={ttx}, ty={tty})")

    ax2.scatter([x1, x2, x3], [y1, y2, y3], c="white", s=40, zorder=4)
    ax2.scatter([x1 + ttx, x2 + ttx, x3 + ttx],
                [y1 + tty, y2 + tty, y3 + tty], c="cyan", s=40, zorder=4)

    ax2.annotate("Original", (x1, y1), xytext=(5, 8),
                 textcoords="offset points", color="white", fontsize=8)
    ax2.annotate("Translated", (x1 + ttx, y1 + tty), xytext=(5, 8),
                 textcoords="offset points", color="cyan", fontsize=8)

    for ax in [ax1, ax2]:
        ax.set_xlabel("X")
        ax.set_ylabel("Y")
        ax.legend(fontsize=8, loc="lower right")
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
