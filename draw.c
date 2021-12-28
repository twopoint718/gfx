#include <stdbool.h>
#include <stdlib.h>
#include "gfx.h"

// x^2 + y^2 = r^2
void draw_circle(int x0, int y0, int r) {
    int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x = 0;
    int y = r;

    // filling in 4 quadrants at once, all symmetric
    set_pixel(x0, y0 - r);  // N
    set_pixel(x0 - r, y0);  // W
    set_pixel(x0, y0 + r);  // S
    set_pixel(x0 + r, y0);  // E

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        // in CCW order
        set_pixel(x0 - x, y0 - y);  // NNW
        set_pixel(x0 - y, y0 - x);  // WNW
        set_pixel(x0 - y, y0 + x);  // WSW
        set_pixel(x0 - x, y0 + y);  // SSW
        set_pixel(x0 + x, y0 + y);  // SSE
        set_pixel(x0 + y, y0 + x);  // ESE
        set_pixel(x0 + y, y0 - x);  // ENE
        set_pixel(x0 + x, y0 - y);  // NNE
    }
}

void draw_line(int x0, int y0, int x1, int y1) {
    _Bool steep = abs(y1 - y0) > abs(x1 - x0);
    int tmp;

    if (steep) {
        tmp = x0; x0 = y0; y0 = tmp; // swap x0, y0
        tmp = x1; x1 = y1; y1 = tmp; // swap x1, y1
    }

    if (x0 > x1) {
        tmp = x0; x0 = x1; x1 = tmp; // swap x0, x1
        tmp = y0; y0 = y1; y1 = tmp; // swap y0, y1
    }

    int dx = x1 - x0;
    int dy = abs(y1 - y0);

    int err = dx / 2;
    int ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0 <= x1; x0++) {
        if (steep) {
            set_pixel(y0, x0);
        } else {
            set_pixel(x0, y0);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

