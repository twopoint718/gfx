#include <stdio.h>
#include "draw.h"
#include "gfx.h"

int main(int argc, char** argv) {
    int x = 0, y = 0;
    for (int i = 0; i < 100; i++) {
        d2xy(100, i, &x, &y);
        set_pixel(x, y);
    }
    draw_render("bitmap.pbm");
}
