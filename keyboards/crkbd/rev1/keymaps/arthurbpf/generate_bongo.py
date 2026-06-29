#!/usr/bin/env python3
"""Generate bongo cat OLED bitmaps for 128x32 SSD1306 display."""

W = 128
H = 32


def draw_cat(grid, arms_up=False):
    """Draw bongo cat centered in grid. grid is H x W (rows x cols)."""
    # Clear
    for y in range(H):
        for x in range(W):
            grid[y][x] = 0

    cx = 56  # cat center x
    cy = 14  # cat center y

    # Ears
    for x in [cx - 14, cx + 10]:
        for i in range(8):
            grid[cy - 9 - i][x + i] = 1
            grid[cy - 9 - i][x + 10 - i] = 1

    # Head outline
    for y in range(cy - 6, cy + 8):
        w = int((1 - ((y - cy) / 8) ** 2) ** 0.5 * 16)
        for x in range(cx - w, cx + w + 1):
            grid[y][x] = 1

    # Head interior clear
    for y in range(cy - 4, cy + 6):
        w = int((1 - ((y - cy) / 7) ** 2) ** 0.5 * 14)
        for x in range(cx - w, cx + w + 1):
            grid[y][x] = 0

    # Eyes
    for x in range(cx - 7, cx - 4):
        grid[cy - 1][x] = 1
        grid[cy][x] = 1
    for x in range(cx + 4, cx + 7):
        grid[cy - 1][x] = 1
        grid[cy][x] = 1

    # Mouth
    for x in range(cx - 4, cx + 5):
        grid[cy + 3][x] = 1

    # Nose
    grid[cy + 1][cx - 1] = 1
    grid[cy + 1][cx] = 1
    grid[cy + 1][cx + 1] = 1

    # Whiskers
    for x in range(cx - 12, cx - 4):
        grid[cy + 1][x] = 1
    for x in range(cx + 4, cx + 12):
        grid[cy + 1][x] = 1

    # Body
    for y in range(cy + 5, cy + 14):
        for x in range(cx - 10, cx + 11):
            grid[y][x] = 1

    # Body interior clear
    for y in range(cy + 7, cy + 12):
        for x in range(cx - 6, cx + 7):
            grid[y][x] = 0

    # Arms
    if arms_up:
        # Arms up with paws
        for y in range(cy + 5, cy + 11):
            grid[y][cx - 12] = 1
            grid[y][cx + 12] = 1
        # Paws
        for x in range(cx - 14, cx - 10):
            grid[cy + 10][x] = 1
            grid[cy + 11][x] = 1
        for x in range(cx + 10, cx + 14):
            grid[cy + 10][x] = 1
            grid[cy + 11][x] = 1
    else:
        # Arms down
        for y in range(cy + 5, cy + 12):
            grid[y][cx - 12] = 1
            grid[y][cx + 12] = 1
        # Paws down
        for x in range(cx - 14, cx - 10):
            grid[cy + 12][x] = 1
        for x in range(cx + 10, cx + 14):
            grid[cy + 12][x] = 1

    # Keyboard/desk line
    if arms_up:
        for x in range(cx - 18, cx + 18):
            for y in range(H - 4, H):
                if (x // 6) % 2 == 0:
                    grid[y][x] = 1
    else:
        for x in range(cx - 18, cx + 18):
            grid[H - 3][x] = 1
            grid[H - 2][x] = 1


def grid_to_oled(grid):
    """Convert HxW pixel grid to SSD1306 format (512 bytes, column-major)."""
    data = []
    pages = H // 8  # 4 pages for 32px height
    for page in range(pages):
        for col in range(W):
            byte = 0
            for bit in range(8):
                y = page * 8 + bit
                if grid[y][col]:
                    byte |= 1 << bit
            data.append(byte)
    return data


def format_c_array(name, data):
    """Format byte array as C source."""
    lines = []
    lines.append(f"static const char PROGMEM {name}[] = {{")
    for i in range(0, len(data), 16):
        chunk = data[i : i + 16]
        line = "    " + ", ".join(f"0x{b:02X}" for b in chunk) + ","
        lines.append(line)
    lines.append("};")
    return "\n".join(lines)


if __name__ == "__main__":
    grid_idle = [[0] * W for _ in range(H)]
    grid_type = [[0] * W for _ in range(H)]

    draw_cat(grid_idle, arms_up=False)
    draw_cat(grid_type, arms_up=True)

    data_idle = grid_to_oled(grid_idle)
    data_type = grid_to_oled(grid_type)

    print("// Bongo cat idle frame (128x32)")
    print(format_c_array("bongo_idle", data_idle))
    print()
    print("// Bongo cat typing frame (128x32)")
    print(format_c_array("bongo_typing", data_type))
