import matplotlib.pyplot as plt


def dda_line(x1, y1, x2, y2):
    dx = x2 - x1
    dy = y2 - y1
    steps = max(abs(dx), abs(dy))
    x_inc = dx / steps
    y_inc = dy / steps

    x, y = float(x1), float(y1)
    pixels = []
    for _ in range(steps + 1):
        pixels.append((round(x), round(y)))
        x += x_inc
        y += y_inc
    return pixels


def run():
    x1, y1 = 100, 100
    x2, y2 = 400, 300

    pixels = dda_line(x1, y1, x2, y2)

    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("DDA Line Algorithm: Digital Differential Analyzer")

    xs, ys = zip(*pixels)
    ax.scatter(xs, ys, c="yellow", s=30, label="DDA Pixels", zorder=3)
    ax.plot([x1, x2], [y1, y2], "r--", linewidth=1, alpha=0.5, label="True line")

    ax.scatter([x1, x2], [y1, y2], c="red", s=80, zorder=4)
    ax.annotate(f"A({x1},{y1})", (x1, y1), xytext=(8, 5),
                textcoords="offset points", color="red", fontsize=9)
    ax.annotate(f"B({x2},{y2})", (x2, y2), xytext=(8, 5),
                textcoords="offset points", color="red", fontsize=9)

    dx, dy = x2 - x1, y2 - y1
    steps = max(abs(dx), abs(dy))
    x_inc = dx / steps
    y_inc = dy / steps

    info = (
        f"dx = {dx}   dy = {dy}\n"
        f"steps = max(|dx|,|dy|) = {steps}\n"
        f"x_inc = dx/steps = {dx}/{steps} = {x_inc:.2f}\n"
        f"y_inc = dy/steps = {dy}/{steps} = {y_inc:.2f}"
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
