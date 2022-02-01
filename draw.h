#ifndef __DRAW_H
#define __DRAW_H

void draw_circle(unsigned int x0, unsigned int y0, unsigned int r);
void draw_line(int x0, int y0, int x1, int y1);
void draw_render(const char*);
void d2xy(int numPoints, int value, int *px, int *py);
int xy2d (int, int, int);
void rot(int, int*, int*, int, int);

#endif // __DRAW_H
