#include <stdio.h>
#include "draw.h"

int main(int argc, char** argv) {
    for (int i = 60; i <= 250 - 60; i += 5)
        draw_circle(i, 122/2, 60);
    draw_render("bitmap.pbm");
    printf("Done\n");
}
