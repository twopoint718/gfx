#include <stdio.h>
#include <stdint.h>
#include "draw.h"
#include "gfx.h"

int main(int argc, char** argv) {
  /* char msg[] = */
  /*   "This place is a message. And part of a system of messages. Pay attention " */
  /*   "to it! Sending this message was important to us. We considered ourselves " */
  /*   "to be a powerful culture. This place is not a place of honor. No highly " */
  /*   "esteemed deed is commemorated here. Nothing valued is here. What is here " */
  /*   "was dangerous and repulsive to us. This message is a warning about " */
  /*   "danger. The danger is in a particular location. it increases towards a " */
  /*   "center. the center of danger is here. of a particular size and shape, and " */
  /*   "below us. The danger is still present, in your time, as it was in ours. " */
  /*   "The danger is to the body, and it can kill The form of the danger is an " */
  /*   "emanation of energy. The danger is unleashed only if you substantially " */
  /*   "disturb this place physically. This place is best shunned and left " */
  /*   "uninhabited."; */

  // for (uint8_t c = 0; c < 128; c++)
  //   for (int col = 0; col < 16; col++)
  //     for (int row = 0; row < 8; row++)
  char c = 0;
  for (int j = 0; j < 64; j += 8)
    for (int i = 0; i < 128; i += 8)
      draw_char8x8(i, j, c++, 1);

  char filename[] = "bitmap.pbm";
  draw_render(filename);
  printf("'%s' written.\n", filename);
}
