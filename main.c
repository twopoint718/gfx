#include <stdio.h>
#include "draw.h"
#include "gfx.h"

int main(int argc, char** argv) {
    draw_circle(125, 60, 60);
    gfx_render();
    printf("Done\n");
}
