"""Add a Windows-style window frame around a matplotlib figure."""

from PIL import Image, ImageDraw


TITLE_BAR_H = 32
BORDER_W = 3
SHADOW_W = 5
CORNER_R = 6

COLOR_TITLE_BG = "#1a1a2e"
COLOR_TITLE_TEXT = "white"
COLOR_BORDER = "#16213e"
COLOR_SHADOW = "#00000040"
COLOR_CLOSE = "#e74c3c"
COLOR_MINIMIZE = "#f39c12"
COLOR_MAXIMIZE = "#2ecc71"
COLOR_CLIENT_BG = "#0f0f23"


def frame_image(image: Image.Image, title: str) -> Image.Image:
    w, h = image.size
    pad = BORDER_W + SHADOW_W
    sw = w + 2 * pad
    sh = h + 2 * pad + TITLE_BAR_H

    framed = Image.new("RGBA", (sw + SHADOW_W, sh + SHADOW_W), (0, 0, 0, 0))
    draw = ImageDraw.Draw(framed)

    # shadow
    shadow_box = (SHADOW_W, SHADOW_W, sw + SHADOW_W, sh + SHADOW_W)
    draw.rounded_rectangle(shadow_box, radius=CORNER_R + 1, fill=COLOR_SHADOW)

    # outer border + title bar background
    box = (0, 0, sw, sh)
    draw.rounded_rectangle(box, radius=CORNER_R, fill=COLOR_BORDER)

    # title bar
    tb_box = (BORDER_W, BORDER_W, sw - BORDER_W, BORDER_W + TITLE_BAR_H)
    draw.rounded_rectangle(tb_box, radius=3, fill=COLOR_TITLE_BG)

    # title text
    text_x = BORDER_W + 10
    text_y = BORDER_W + 6
    draw.text((text_x, text_y), title, fill=COLOR_TITLE_TEXT)

    # window control buttons
    btn_y = BORDER_W + 7
    btn_r = 6
    btn_spacing = 20
    right_x = sw - BORDER_W - 12
    for color in (COLOR_CLOSE, COLOR_MINIMIZE, COLOR_MAXIMIZE):
        cx, cy = right_x, btn_y + btn_r
        draw.ellipse((cx - btn_r, cy - btn_r, cx + btn_r, cy + btn_r), fill=color)
        right_x -= btn_spacing

    # client area background
    client_box = (
        BORDER_W,
        BORDER_W + TITLE_BAR_H,
        sw - BORDER_W,
        sh - BORDER_W,
    )
    draw.rounded_rectangle(client_box, radius=2, fill=COLOR_CLIENT_BG)

    # paste original image
    paste_x = BORDER_W
    paste_y = BORDER_W + TITLE_BAR_H
    framed.paste(image, (paste_x, paste_y))

    # crop excess shadow
    return framed.crop((0, 0, sw + SHADOW_W, sh + SHADOW_W)).convert("RGB")


def save_framed(image_path: str, title: str, output_path: str = None):
    img = Image.open(image_path).convert("RGBA")
    framed = frame_image(img, title)
    out = output_path or image_path
    framed.save(out, quality=95)
