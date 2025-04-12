#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE* filePointer = fopen(filename, "rb");

  char magic[3]; // reading first two characters (P6) and new line using fgets
  fgets(magic, sizeof(magic), filePointer);
  
  char comment[128];
  while (fgets(comment, sizeof(comment), filePointer)) {
    if (comment[0] == '#') {
      continue; // ignore comment
    }
    if (sscanf(comment, "%d %d", w, h) == 2) {
      break; // reached the dimenson value so break while loop
    }
  }

  // use fgetc to consume maxval and single whitespace character
  fgetc(filePointer); 
  fgetc(filePointer);
  
  // allocate memory for array storing pixels
  struct ppm_pixel* pixel_array = malloc(sizeof(struct ppm_pixel) * (*w) * (*h));

  // inserting pixels into array
  fread(pixel_array, sizeof(struct ppm_pixel), (*w) * (*h), filePointer);

  fclose(filePointer);
  return pixel_array;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {

  return NULL;
}
