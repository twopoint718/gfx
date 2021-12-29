#include <stdio.h>
#include "gfx.h"
#include "pbm.h"

// 250 x 122
#define ROWS 122
#define COLS 250

// ceiling(COLS / 8), pixels are packed into bytes
uint8_t screen[COLS / 8 + (COLS % 8 != 0)][ROWS];

/* e.g.
 * Write to pixel (13, 0)
 *
 *   byte_offset: 13/8=1
 *            │
 *            ▼
 *   ┌────────┬────────┬────────┬────────┐
 *   │ byte 0 │76543210│  ...   │byte 31 │ Row 0
 *   └────────┴─────▲──┴────────┴────────┘
 *                  │
 *       bit_offset: 7-(13%8)=2
 */
void set_pixel(int x, int y) {
    int offset = 7 - (x % 8);
    screen[x / 8][y] |= (1 << offset);
}

void clear_pixel(int x, int y) {
    int offset = 7 - (x % 8);
    screen[x / 8][y] &= ~(1 << offset);
}

void clear_screen() {
    for (int j = 0; j < ROWS; j++)
        for (int i = 0; i < COLS; i++)
            screen[i][j] = 0x00;
}

void gfx_render(const char *filename) {
    render(filename, COLS, ROWS, screen);
}
