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
