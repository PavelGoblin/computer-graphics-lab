import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

INSIDE = 0
LEFT = 1
RIGHT = 2
BOTTOM = 4
TOP = 8

XMIN, YMIN = 150, 100
XMAX, YMAX = 450, 300


def compute_code(x, y):
    code = INSIDE
    if x < XMIN:
        code |= LEFT
    elif x > XMAX:
        code |= RIGHT
    if y < YMIN:
        code |= TOP
    elif y > YMAX:
        code |= BOTTOM
    return code


def cohen_sutherland_clip(x1, y1, x2, y2):
    code1 = compute_code(x1, y1)
    code2 = compute_code(x2, y2)
    accept = False

    while True:
        if code1 == 0 and code2 == 0:
            accept = True
            break
        elif code1 & code2:
            break
        else:
            code_out = code1 if code1 != 0 else code2

            if code_out & TOP:
                x = x1 + (x2 - x1) * (YMIN - y1) / (y2 - y1)
                y = YMIN
            elif code_out & BOTTOM:
                x = x1 + (x2 - x1) * (YMAX - y1) / (y2 - y1)
                y = YMAX
            elif code_out & RIGHT:
                y = y1 + (y2 - y1) * (XMAX - x1) / (x2 - x1)
                x = XMAX
            elif code_out & LEFT:
                y = y1 + (y2 - y1) * (XMIN - x1) / (x2 - x1)
                x = XMIN

            if code_out == code1:
                x1, y1 = x, y
                code1 = compute_code(x1, y1)
            else:
                x2, y2 = x, y
                code2 = compute_code(x2, y2)

    if accept:
        return (round(x1), round(y1), round(x2), round(y2))
    return None


def run():
    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("Cohen-Sutherland Line Clipping")
    ax.set_xlim(0, 640)
    ax.set_ylim(0, 480)
    ax.set_aspect("equal")
    ax.grid(True, alpha=0.3)

    win = mpatches.Rectangle(
        (XMIN, YMIN), XMAX - XMIN, YMAX - YMIN,
        fill=False, edgecolor="white", linewidth=2, label="Clipping Window"
    )
    ax.add_patch(win)
    ax.text(XMIN + 5, YMIN - 15, "Clipping Window", color="white", fontsize=8)

    lines = [
        (50, 200, 300, 80),
        (500, 250, 300, 350),
        (100, 150, 200, 250),
        (50, 50, 100, 80),
        (500, 350, 550, 400),
        (200, 50, 350, 50),
        (500, 150, 300, 200),
    ]

    for x1, y1, x2, y2 in lines:
        ax.plot([x1, x2], [y1, y2], "w-", linewidth=1, alpha=0.4)

    for x1, y1, x2, y2 in lines:
        clipped = cohen_sutherland_clip(x1, y1, x2, y2)
        if clipped:
            cx1, cy1, cx2, cy2 = clipped
            ax.plot([cx1, cx2], [cy1, cy2], "y-", linewidth=2.5)

    ax.text(0.02, 0.98,
            "White = Original lines (faded)\n"
            "Yellow = Visible portion after clip",
            transform=ax.transAxes, fontsize=10, verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="wheat", alpha=0.8))

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.legend(fontsize=8, loc="lower right")
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    run()
