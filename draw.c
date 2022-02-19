#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "draw.h"
#include "gfx.h"
#include "glcdfont.c"
#include "font8x8_basic.h"
#include "pbm.h"

// Adafruit implementation
void draw_circle_af(int x0, int y0, int r) {
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

// via: https://github.com/possibly-wrong/string-art
// Call plot(_, _) to draw pixels on circle at origin with given radius.
void draw_arc(int cx, int cy, int radius, int arc, void(*plot)(int, int)) {
    int x = radius;
    int y = 0;
    int error = 3 - 2 * radius;
    draw_line(cx, cy, cx, cy-radius);
    while (x >= y) {
        if (arc >= 0) { plot(cx+y, cy-x); draw_line(cx,cy,cx+y,cy-x);} //   0, 45
        if (arc >= 1) { plot(cx+x, cy-y); draw_line(cx,cy,cx+x,cy-y);} //  45, 90
        if (arc >= 2) { plot(cx+x, cy+y); draw_line(cx,cy,cx+x,cy+y);} //  90,145
        if (arc >= 3) { plot(cx+y, cy+x); draw_line(cx,cy,cx+y,cy+x);} // 135,180
        if (arc >= 4) { plot(cx-y, cy+x); draw_line(cx,cy,cx-y,cy+x);} // 180,225
        if (arc >= 5) { plot(cx-x, cy+y); draw_line(cx,cy,cx-x,cy+y);} // 225,270
        if (arc >= 6) { plot(cx-x, cy-y); draw_line(cx,cy,cx-x,cy-y);} // 270,315
        if (arc >= 7) { plot(cx-y, cy-x); draw_line(cx,cy,cx-y,cy-x);} // 315,360
        if (error > 0) {
            error -= 4 * (--x);
        }
        error += 4 * (++y) + 2;
    }
}

void draw_circle(unsigned int x, unsigned int y, unsigned int r) {
    int di = 3 - 2 * r; // initial 'decision parameter', see derivation [0]
    int xi = 0;
    int yi = r;

    while (xi <= yi) {
        set_pixel(xi + x, yi + y);
        set_pixel(x - xi, yi + y);
        set_pixel(xi + x, y - yi);
        set_pixel(x - xi, y - yi);

        set_pixel(yi + x, xi + y);
        set_pixel(x - yi, y + xi);
        set_pixel(x + yi, y - xi);
        set_pixel(x - yi, y - xi);
        if (di <= 0) {
            di = di + 4 * xi + 6;           // see derivation [1]
            xi = xi + 1;
            // yi remains the same
        } else {
            di = di + 4 * (xi - yi) + 10;   // see derivation [2]
            xi = xi + 1;
            yi = yi - 1;
        }
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

////////////////////////////////////////////////////////////////////////////////
// Converting 1-D to 2-D and vice versa via the Hilbert curve (Wikipedia)

/** convert (x,y) to d
 */
int xy2d (int n, int x, int y) {
    int rx, ry, s, d=0;
    for (s=n/2; s>0; s/=2) {
        rx = (x & s) > 0;
        ry = (y & s) > 0;
        d += s * s * ((3 * rx) ^ ry);
        rot(n, &x, &y, rx, ry);
    }
    return d;
}

/** convert d to (x,y)
 */
void d2xy(int n, int d, int *x, int *y) {
    int rx, ry, s, t=d;
    *x = *y = 0;
    for (s=1; s<n; s*=2) {
        rx = 1 & (t/2);
        ry = 1 & (t ^ rx);
        rot(s, x, y, rx, ry);
        *x += s * rx;
        *y += s * ry;
        t /= 4;
    }
}

/** rotate/flip a quadrant appropriately
 */
void rot(int n, int *x, int *y, int rx, int ry) {
    if (ry == 0) {
        if (rx == 1) {
            *x = n-1 - *x;
            *y = n-1 - *y;
        }

        //Swap x and y
        int t  = *x;
        *x = *y;
        *y = t;
    }
}

void draw_render(const char *filename) {
    gfx_render(filename);
}

// Draw a character
/**************************************************************************/
/*!
   @brief   Draw a single character
    @param    x   Bottom left corner x coordinate
    @param    y   Bottom left corner y coordinate
    @param    c   The 8-bit font-indexed character (likely ascii)
    @param    color 16-bit 5-6-5 Color to draw chraracter with
    @param    bg 16-bit 5-6-5 Color to fill background with (if same as color,
   no background)
    @param    size_x  Font magnification level in X-axis, 1 is 'original' size
    @param    size_y  Font magnification level in Y-axis, 1 is 'original' size
*/
/**************************************************************************/
void draw_char(int16_t x, int16_t y, unsigned char c, unsigned char color) {
    if ((x >= LCDWIDTH) || (y >= LCDHEIGHT) || (x < 0) || (y < 0)) // clip
        return;

    for (int8_t i = 0; i < 5; i++) {                // Char bitmap = 5 columns
        char line = font[c * 5 + i];             // Get ith col of font glyph
        for (int8_t j = 0; j < 8; j++, line >>= 1) {
            if (line & 1) {
                set_pixel(x + i, y + j);
            }
        }
    }
}

void draw_char8x8(int16_t x, int16_t y, unsigned char c, unsigned char color) {
    if ((x >= LCDWIDTH) || (y >= LCDHEIGHT) || (x < 0) || (y < 0)) // clip
        return;

    for (int8_t j = 0; j < 8; j++) {
        char row = font8x8_basic[c][j];
        for (int8_t i = 0; i < 8; i++, row >>= 1)
            if (row & 1)
                set_pixel(x + i, y + j);
    }
}
