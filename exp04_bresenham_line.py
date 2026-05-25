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
        (cx, cy, cx + 150, cy),
        (cx, cy, cx + 100, cy - 80),
        (cx, cy, cx, cy - 150),
        (cx, cy, cx - 100, cy - 80),
        (cx, cy, cx - 150, cy),
        (cx, cy, cx - 100, cy + 80),
        (cx, cy, cx, cy + 150),
        (cx, cy, cx + 100, cy + 80),
    ]

    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("Bresenham Line Algorithm (Integer Arithmetic)")

    colors = plt.cm.tab10.colors
    all_pixels = []
    for i, (x1, y1, x2, y2) in enumerate(endpoints):
        pixels = bresenham_line(x1, y1, x2, y2)
        all_pixels.extend(pixels)
        xs, ys = zip(*pixels)
        ax.scatter(xs, ys, color=colors[i % len(colors)], s=20, zorder=3)

    ax.scatter([cx], [cy], c="red", s=100, zorder=4, marker="o")
    ax.annotate(f"Center ({cx},{cy})", (cx, cy),
                xytext=(8, 5), textcoords="offset points",
                color="red", fontsize=9, fontweight="bold")

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
