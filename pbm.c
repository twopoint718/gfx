#include <stdio.h>
#include "pbm.h"

void render(const char *filename, int x, int y, uint8_t data[x][y]) {
    int offset;
    FILE *file = fopen(filename, "w");
    fprintf(file, "P1\n%i %i\n", x, y);
    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            offset = 7 - (i % 8);
            fprintf(file, "%d ", (data[i / 8][j] & 1<<offset) ? 1 : 0);
        }
        fprintf(file, "\n");
    }
}
