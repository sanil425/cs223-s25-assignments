#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
  FILE* filePointer = fopen(filename, "wb"); 
  if (!filePointer) {
    fprintf(stderr, "Error: Cannot open file %s for writing\n", filename);
    return;
  }
  fprintf(filePointer, "P6\n%d %d\n255\n", w, h); // header

    // juliette helped me out with this block
  if (fwrite(pixels, sizeof(struct ppm_pixel), w * h, filePointer) != (size_t)(w * h)) {
    fprintf(stderr, "Error: Failed to write pixel data\n"); // should return w * h as it returns number of bytes sucessfully written
  }

  fclose(filePointer);
}

void write_ppm_2d(const char* filename, struct ppm_pixel** pxs, int w, int h) {
}
