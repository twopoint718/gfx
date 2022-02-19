#include <stdio.h>
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


  int wedge = 0;
  for (int cy = 20; cy <= 60; cy += 40)
    for (int cx = 20; cx <= 220; cx += 40)
      draw_arc(cx, cy, 20, wedge++, &set_pixel);

  char filename[] = "bitmap.pbm";
  draw_render(filename);
  printf("'%s' written.\n", filename);
}
