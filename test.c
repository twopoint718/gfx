#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "gfx.h"

// Examine internal screen state
extern uint8_t screen[32][122];

//  01234567   89ABCDEF
// [76543210] [76543210]
//   byte 0     byte 1

void test_setting_pixel() {
    set_pixel(13, 0);
    assert(screen[1][0] == 0x04);
    screen[1][0] = 0;
    putchar('.');
}

void test_edge_pixel_high() {
    set_pixel(7, 0);
    set_pixel(15, 0);
    assert(screen[0][0] == 0x01);
    assert(screen[1][0] == 0x01);
    screen[0][0] = 0;
    screen[1][0] = 0;
    putchar('.');
    putchar('.');
}

void test_edge_pixel_low() {
    set_pixel(0, 0);
    set_pixel(9, 0);
    assert(screen[0][0] == 0x80);
    assert(screen[1][0] == 0x80);
    screen[0][0] = 0;
    screen[1][0] = 0;
    putchar('.');
    putchar('.');
}


int main(int argc, char** argv) {
    test_setting_pixel();
    test_edge_pixel_high();
    printf("\nSuccess\n");
    return 0;
}
