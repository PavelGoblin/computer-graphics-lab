import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

XMIN, YMIN = 150, 100
XMAX, YMAX = 450, 300


def inside(p, edge):
    x, y = p
    if edge == 0:
        return x >= XMIN
    if edge == 1:
        return x <= XMAX
    if edge == 2:
        return y >= YMIN
    if edge == 3:
        return y <= YMAX
    return False


def intersect(p1, p2, edge):
    x1, y1 = p1
    x2, y2 = p2

    if x2 != x1:
        m = (y2 - y1) / (x2 - x1)
    else:
        m = 1e10

    if edge == 0:
        return (XMIN, round(y1 + m * (XMIN - x1)))
    if edge == 1:
        return (XMAX, round(y1 + m * (XMAX - x1)))
    if edge == 2:
        if x2 != x1:
            x = round(x1 + (YMIN - y1) / m)
        else:
            x = x1
        return (x, YMIN)
    if edge == 3:
        if x2 != x1:
            x = round(x1 + (YMAX - y1) / m)
        else:
            x = x1
        return (x, YMAX)
    return (0, 0)


def clip_against_edge(poly, edge):
    if not poly:
        return []
    result = []
    n = len(poly)
    for i in range(n):
        curr = poly[i]
        nxt = poly[(i + 1) % n]
        curr_inside = inside(curr, edge)
        nxt_inside = inside(nxt, edge)

        if curr_inside and nxt_inside:
            result.append(nxt)
        elif curr_inside and not nxt_inside:
            result.append(intersect(curr, nxt, edge))
        elif not curr_inside and nxt_inside:
            result.append(intersect(curr, nxt, edge))
            result.append(nxt)
    return result


def draw_polygon(ax, poly, color, linewidth=2):
    if len(poly) < 3:
        return
    xs, ys = zip(*(poly + [poly[0]]))
    ax.plot(xs, ys, color=color, linewidth=linewidth)


def run():
    fig, ax = plt.subplots(figsize=(8, 6))
    ax.set_title("Sutherland-Hodgman Polygon Clipping")
    ax.axhline(0, color='gray', linewidth=0.8, alpha=0.5)
    ax.axvline(0, color='gray', linewidth=0.8, alpha=0.5)
    ax.set_xlim(-50, 600)
    ax.set_ylim(-50, 450)
    ax.set_aspect("equal")
    ax.grid(True, alpha=0.3)

    win = mpatches.Rectangle(
        (XMIN, YMIN), XMAX - XMIN, YMAX - YMIN,
        fill=False, edgecolor="white", linewidth=2, label="Clipping Window"
    )
    ax.add_patch(win)
    ax.text(XMIN + 5, YMIN - 15, "Clipping Window", color="white", fontsize=8)

    polygon = [
        (80, 80), (200, 50), (350, 120), (500, 100),
        (520, 250), (400, 350), (100, 280), (50, 200),
    ]

    draw_polygon(ax, polygon, "white", 1.5)

    clipped = polygon[:]
    for edge in range(4):
        clipped = clip_against_edge(clipped, edge)

    draw_polygon(ax, clipped, "yellow", 2.5)

    if clipped:
        cx = sum(p[0] for p in clipped) // len(clipped)
        cy = sum(p[1] for p in clipped) // len(clipped)
        ax.text(cx - 20, cy, "Clipped", color="yellow", fontsize=9, fontweight="bold")

    ax.text(0.02, 0.98,
            "White = Original polygon\n"
            "Yellow = After clipping against window",
            transform=ax.transAxes, fontsize=10, verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="wheat", alpha=0.8))

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.legend(fontsize=8, loc="lower right")
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    run()
