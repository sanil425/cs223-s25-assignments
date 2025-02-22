/*----------------------------------------------
 * Author: Sanil Kagalwala
 * Date: 20th February 2025
 * Description
 * Implements function that can read PPM files
 * stored in binary format.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement (do not remove the other one!)

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  return NULL;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  FILE* file = fopen(filename, "rb");
  // Read file in and ensure read correctly
  if (!file) { 
    printf("Error opening file %s\n", filename);
    return NULL;
  }

  // Read the PPM header P6
  char magic_num[3];
  char buffer[256]; // temporary buffer for reading lines

  // Read first line for magic number
  fgets(buffer, sizeof(buffer), file); // Read first line into buffer
  sscanf(buffer, "%2s", magic_num); // Extract 2 numbers (P6)
  magic_num[2] = '\0'; // ensure there is a null terminator

  // read next line (but check if its a comment)
  fgets(buffer, sizeof(buffer), file); // read next line into buffer
  while (buffer[0] == '#') {
    fgets(buffer, sizeof(buffer), file); // read next line if comment
  }

  sscanf(buffer, "%d %d", w, h); // Assign values to pointers w and h
  
  fgets(buffer, sizeof(buffer), file); // Read next line and read in max colour
  int max_colour_val;
  sscanf(buffer, "%d", &max_colour_val);

  fgetc(file); // consumes the proceeding whitespace

  // Create matrix pixels which is a double pointer
  // malloc allocates memory for array of h pointers
  struct ppm_pixel** pixels = malloc((*h) * sizeof(struct ppm_pixel*));
  if (pixels == NULL) {
    fclose(file);
    return NULL; // Return NULL if memory allocation fails
  // Allocates a row of w pixels. pixel[i] stores pointer to array of w pixels
  for (int i = 0; i < *h; i++) {
    pixels[i] = malloc((*w) * sizeof(struct ppm_pixel));
    // Check if memory allocation fail, if so free all
    if (pixels[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(pixels[j]);
      }
      free(pixels);
      fclose(file);
      return NULL;
    }
  }

  // For each row of pixels, reads w number of info from ppm_pixel
  // fread reads raw binary so use to read in data
  for (int i = 0; i < *h; i++) {
    fread(pixels[i], sizeof(struct ppm_pixel), *w, file);
  }
	
  fclose(file);

  return pixels; // return pointer to 2d array created
}
