import matplotlib.pyplot as plt


def slope_intercept_line(x1, y1, x2, y2):
    dx = x2 - x1
    dy = y2 - y1

    if dx == 0:
        y_start = min(y1, y2)
        y_end = max(y1, y2)
        return [(x1, y) for y in range(y_start, y_end + 1)]

    m = dy / dx
    c = y1 - m * x1
    pixels = []

    if abs(dx) >= abs(dy):
        x_start = min(x1, x2)
        x_end = max(x1, x2)
        for x in range(x_start, x_end + 1):
            y_exact = m * x + c
            pixels.append((x, round(y_exact)))
    else:
        y_start = min(y1, y2)
        y_end = max(y1, y2)
        for y in range(y_start, y_end + 1):
            x_exact = (y - c) / m
            pixels.append((round(x_exact), y))

    return pixels, m, c


def run():
    x1, y1 = 100, 100
    x2, y2 = 400, 300

    result = slope_intercept_line(x1, y1, x2, y2)
    pixels, m, c = result

    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("Slope-Intercept: y = mx + c")
    ax.axhline(0, color='k', linewidth=0.8)
    ax.axvline(0, color='k', linewidth=0.8)
    ax.set_xlim(-50, 450)
    ax.set_ylim(-50, 350)

    xs, ys = zip(*pixels)
    ax.scatter(xs, ys, c="yellow", s=30, label="Line pixels", zorder=3)
    ax.plot([x1, x2], [y1, y2], "r--", linewidth=1, alpha=0.5, label="True line")

    ax.scatter([x1, x2], [y1, y2], c="red", s=80, zorder=4)
    ax.annotate(f"A({x1},{y1})", (x1, y1), xytext=(8, 5),
                textcoords="offset points", color="red", fontsize=9)
    ax.annotate(f"B({x2},{y2})", (x2, y2), xytext=(8, 5),
                textcoords="offset points", color="red", fontsize=9)

    dx, dy = x2 - x1, y2 - y1
    info = (
        f"dx = {dx}   dy = {dy}\n"
        f"m = dy/dx = {dy}/{dx} = {m:.2f}\n"
        f"c = y1 - m*x1 = {y1} - ({m:.2f})*{x1} = {c:.2f}\n"
        f"Equation: y = {m:.2f}x + {c:.2f}"
    )
    ax.text(0.02, 0.98, info, transform=ax.transAxes,
            fontsize=9, verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="wheat", alpha=0.8))

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.grid(True, alpha=0.3)
    ax.legend(fontsize=9)
    ax.set_aspect("equal")

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    run()
