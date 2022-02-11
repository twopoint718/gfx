#ifndef __PBM_H
#define __PBM_H

#include <stdio.h>
#include <stdint.h>

/*
 * A simple implementation of Netpbm (just the P1, bitmap format) for image
 * file output. This renders a standard header, then image data to a file.
 */

#define LCDWIDTH 250
#define LCDHEIGHT 122

// render takes an open FILE handle, x and y dimensions of the image and then
// the actual data to be written.
void render(const char*, int x, int y, uint8_t[x][y]);

#endif // __PBM_H
