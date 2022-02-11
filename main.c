#include <stdio.h>
#include "draw.h"
#include "gfx.h"

int main(int argc, char** argv) {
  char msg[] =
    "This place is a message. And part of a system of messages. Pay attention "
    "to it! Sending this message was important to us. We considered ourselves "
    "to be a powerful culture. This place is not a place of honor. No highly "
    "esteemed deed is commemorated here. Nothing valued is here. What is here "
    "was dangerous and repulsive to us. This message is a warning about "
    "danger. The danger is in a particular location. it increases towards a "
    "center. the center of danger is here. of a particular size and shape, and "
    "below us. The danger is still present, in your time, as it was in ours. "
    "The danger is to the body, and it can kill The form of the danger is an "
    "emanation of energy. The danger is unleashed only if you substantially "
    "disturb this place physically. This place is best shunned and left "
    "uninhabited.";

  int row = 0;
  int col = 0;
  int fill_col = 30;
  int fill_row = 14;
  for (int i = 0; i < sizeof(msg); i++) {
    draw_char8x8(col * 8 + 1, row * 8 + 1, msg[i], 1);
    col++;
    if (col > fill_col) {
      row++;
      col = 0;
    }
    if (row > fill_row) {
      break;
    }
  }

  char filename[] = "bitmap.pbm";
  draw_render(filename);
  printf("'%s' written.\n", filename);
}
