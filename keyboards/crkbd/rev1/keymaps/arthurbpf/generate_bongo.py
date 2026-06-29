#!/usr/bin/env python3
"""Minimal bongo cat pixel art for 128x32 OLED."""

W, H = 128, 32

# Cat design as text grid (each char = 2x2 pixels on OLED)
# Width: 32 chars = 64 pixels. Height: 16 chars = 32 pixels.
# '.' = blank, '#' = filled
IDLE = [
    "................................",
    "................................",
    "...........######..............",
    "..........########.............",
    ".........#..#..#..#............",
    "........#..........#...........",
    ".......#..##....##..#..........",
    ".......#..##....##..#..........",
    ".......#............#..........",
    ".......#............#..........",
    "........#..######..#...........",
    ".........#........#............",
    "..........#..##..#.............",
    "...........######..............",
    "................................",
    "................................",
]

# Typing frame: same face but bigger mouth and blush marks
TYPE = [
    "................................",
    "................................",
    "...........######..............",
    "..........########.............",
    ".........#..#..#..#............",
    "........#..........#...........",
    ".......#..##....##..#..........",
    ".......#..##....##..#..........",
    ".......#..##....##..#..........",
    ".......#..##....##..#..........",
    "........#..........#...........",
    ".........#..####..#............",
    "..........#..##..#.............",
    "...........######..............",
    "................................",
    "................................",
]


def text_to_grid(text):
    """Convert text art to pixel grid. Each char = 2x2 pixels."""
    g = [[0] * W for _ in range(H)]
    ox = 20  # x offset from left (in pixels)
    oy = 2  # y offset from top
    for row, line in enumerate(text):
        for col, ch in enumerate(line):
            if ch == "#":
                # Fill 2x2 pixel block
                for dy in range(2):
                    for dx in range(2):
                        py = oy + row * 2 + dy
                        px = ox + col * 2 + dx
                        if 0 <= px < W and 0 <= py < H:
                            g[py][px] = 1
    return g


def grid_to_oled(grid):
    data = []
    for page in range(4):
        for col in range(W):
            byte = 0
            for bit in range(8):
                if grid[page * 8 + bit][col]:
                    byte |= 1 << bit
            data.append(byte)
    return data


def format_c_array(name, data):
    lines = [f"static const char PROGMEM {name}[] = {{"]
    for i in range(0, len(data), 16):
        chunk = data[i : i + 16]
        lines.append("    " + ", ".join(f"0x{b:02X}" for b in chunk) + ",")
    lines.append("};")
    return "\n".join(lines)


if __name__ == "__main__":
    g_idle = text_to_grid(IDLE)
    g_type = text_to_grid(TYPE)

    idle = grid_to_oled(g_idle)
    typing = grid_to_oled(g_type)

    # Print preview
    for line in IDLE:
        print(line)
    print()

    print("// Bongo cat idle frame (128x32)")
    print(format_c_array("bongo_idle", idle))
    print()
    print("// Bongo cat typing frame (128x32)")
    print(format_c_array("bongo_typing", typing))
