/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  int w, h;
  struct ppm_pixel** pixels = read_ppm_2d("feep-raw.ppm", &w, &h);

  if (pixels == NULL) {
    printf("Error reading PPM file\n");
    return 1;
  }
  
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("(%d,%d,%d) ", pixels[i][j].red, pixels[i][j].green,
 	      pixels[i][j].blue);
    } 
    printf("\n");
  }
  // User has to free allocated memory
  for (int i = 0; i < h; i++) {
    free(pixels[i]);
  }
  free(pixels);

  return 0;
}

