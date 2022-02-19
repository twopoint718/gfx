#ifndef __DRAW_H
#define __DRAW_H

#include <stdint.h>

void draw_circle(unsigned int x0, unsigned int y0, unsigned int r);
void draw_arc(int cx, int cy, int radius, int arc, void(*plot)(int, int));
void draw_line(int x0, int y0, int x1, int y1);
void draw_render(const char*);
void d2xy(int numPoints, int value, int *px, int *py);
int xy2d (int, int, int);
void rot(int, int*, int*, int, int);
void draw_char(int16_t x, int16_t y, unsigned char c, unsigned char color);
void draw_char8x8(int16_t x, int16_t y, unsigned char c, unsigned char color);

#endif // __DRAW_H
