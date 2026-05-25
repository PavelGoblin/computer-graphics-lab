import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np


def rotate_about_axis(point, a1, a2, angle):
    px = point[0] - a1[0]
    py = point[1] - a1[1]
    pz = point[2] - a1[2]

    ax = a2[0] - a1[0]
    ay = a2[1] - a1[1]
    az = a2[2] - a1[2]

    length = math.sqrt(ax*ax + ay*ay + az*az)
    ux, uy, uz = ax/length, ay/length, az/length

    rad = math.radians(angle)
    cos_a, sin_a = math.cos(rad), math.sin(rad)

    dot = px*ux + py*uy + pz*uz
    cross_x = uy*pz - uz*py
    cross_y = uz*px - ux*pz
    cross_z = ux*py - uy*px

    new_x = px*cos_a + cross_x*sin_a + ux*dot*(1 - cos_a)
    new_y = py*cos_a + cross_y*sin_a + uy*dot*(1 - cos_a)
    new_z = pz*cos_a + cross_z*sin_a + uz*dot*(1 - cos_a)

    return (round(new_x + a1[0]), round(new_y + a1[1]), round(new_z + a1[2]))


def draw_cube_3d(ax, vertices, color, label=None):
    edges = [
        (0, 1), (1, 2), (2, 3), (3, 0),
        (4, 5), (5, 6), (6, 7), (7, 4),
        (0, 4), (1, 5), (2, 6), (3, 7)
    ]
    xs, ys, zs = zip(*vertices)
    for i, j in edges:
        ax.plot3D(*zip(vertices[i], vertices[j]), color=color, linewidth=1.5)
    ax.scatter(xs, ys, zs, c=color, s=30)


def run():
    cube = [
        (250, 150, -50), (350, 150, -50),
        (350, 250, -50), (250, 250, -50),
        (250, 150,  50), (350, 150,  50),
        (350, 250,  50), (250, 250,  50),
    ]

    a1 = (260, 160, -40)
    a2 = (340, 240, 40)

    rotated_45 = [rotate_about_axis(v, a1, a2, 45) for v in cube]
    rotated_90 = [rotate_about_axis(v, a1, a2, 90) for v in cube]

    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection="3d")
    ax.set_title("3D Rotation About Arbitrary Axis (Body Diagonal)")

    draw_cube_3d(ax, cube, "white", "Original")
    draw_cube_3d(ax, rotated_45, "yellow", "Rotated 45 deg")
    draw_cube_3d(ax, rotated_90, "cyan", "Rotated 90 deg")

    ax.text(0.02, 0.98, 0.98,
            "White = Original | Yellow = 45deg | Cyan = 90deg\n"
            "Rotation axis = cube body diagonal",
            transform=ax.transAxes, fontsize=10, verticalalignment="top",
            bbox=dict(boxstyle="round", facecolor="lightcyan", alpha=0.8))

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")
    ax.set_facecolor("#2b2b2b")
    fig.patch.set_facecolor("#2b2b2b")
    ax.xaxis.label.set_color("white")
    ax.yaxis.label.set_color("white")
    ax.zaxis.label.set_color("white")
    ax.title.set_color("white")
    ax.tick_params(colors="white")

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    run()
