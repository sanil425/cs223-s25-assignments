/*------------------------------------------------
 * Author: Sanil Kagalwala
 * Date: 11th April 2025
 * File: glow.c
 * Description: Applies a glow filter to a PPM image using a single thread.
 *------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"


// function creates new image with only pixels above brightness threshold
struct ppm_pixel* bright_areas(struct ppm_pixel* image, int w, int h, int threshold) {

  // allocate memory for the result image
  struct ppm_pixel* bright_image = malloc(sizeof(struct ppm_pixel) * w * h);
  if (!bright_image) {
    fprintf(stderr, "Error: Failed to allocate memory for bright image\n");
    return NULL;
  }

  // loop through every pixel in the image
  for (int i = 0; i < w * h; i++) {
    // employ brightness formula
    int brightness = (image[i].red + image[i].green + image[i].blue) / 3;

    // if condition: if pixel passes threshold, copy it otherwise make it black
    if (brightness > threshold) {
      bright_image[i] = image[i];
    }
    else {
      bright_image[i].red = 0;
      bright_image[i].green = 0;
      bright_image[i].blue = 0;
    }
  }
  return bright_image;
}

// applies box blur by replacing every pixel with average of the pixels in surrounding box
struct ppm_pixel* blur_image(struct ppm_pixel* image, int w, int h, int box_size) {

  // allocate memory for the result image
  struct ppm_pixel* blur_image = malloc(sizeof(struct ppm_pixel) * w * h);
  if (!blur_image) {
    fprintf(stderr, "Error: Failed to allocate memory for blurred image\n");
    return NULL;
  }

  // loop through each pixel, using nested loop to simulate coordinates
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      
      int red = 0;
      int green = 0;
      int blue = 0;
      int count = 0;

      // blur box for pixel (x,y)
      for (int dy = -box_size/2; dy <= box_size/2; dy++) { // vertical axis
        for (int dx = -box_size/2; dx <= box_size/2; dx++) { // horizontal axis
          int nx = x + dx; // neighbor x
          int ny = y + dy; // neighbor y

          // ensure the box doesn't exceed image bounds
          if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
            int index = ny * w + nx; // find 1D index equivalent

            // accumulate color values
            red += image[index].red;
            green += image[index].green;
            blue += image[index].blue;

            count++; // increment pixel count for averaging
          }
        }
      }

      // compute average color and update pixel at (x,y)
      int index = y * w + x; // 1D index for the current pixel
      blur_image[index].red   = red / count;
      blur_image[index].green = green / count;
      blur_image[index].blue  = blue / count;
    }
  }
  return blur_image;
}

// adds the blurred image back to the original image to create glow effect
struct ppm_pixel* add_glow(struct ppm_pixel* image, struct ppm_pixel* blur_image, int w, int h) {
  struct ppm_pixel* glow_image = malloc(sizeof(struct ppm_pixel) * w * h);
  if (!glow_image) {
    fprintf(stderr, "Error: Failed to allocate memory for glow image\n");
    return NULL;
  }

  // iterate through all pixels and add original image and blurred image
  for (int i = 0; i < w * h; i++) {
    glow_image[i].red = image[i].red + blur_image[i].red;
    if (glow_image[i].red > 255) glow_image[i].red = 255;

    glow_image[i].green = image[i].green + blur_image[i].green;
    if (glow_image[i].green > 255) glow_image[i].green = 255;

    glow_image[i].blue = image[i].blue + blur_image[i].blue;
    if (glow_image[i].blue > 255) glow_image[i].blue = 255;
  }

  return glow_image;
}


int main(int argc, char* argv[]) {
  int w, h;
  int threshold = 200;
  int blur_size = 25;

  // read the original image from file
  struct ppm_pixel* image = read_ppm("earth-small.ppm", &w, &h);
  if (!image) {
    fprintf(stderr, "Error: Failed to read image.\n");
    return 1;
  }

  // bright areas
  struct ppm_pixel* bright = bright_areas(image, w, h, threshold);
  if (!bright) {
    free(image);
    return 1;
  }

  // blur
  struct ppm_pixel* blurred = blur_image(bright, w, h, blur_size);
  if (!blurred) {
    free(image);
    free(bright);
    return 1;
  }

  // glow
  struct ppm_pixel* glow = add_glow(image, blurred, w, h);
  if (!glow) {
    free(image);
    free(bright);
    free(blurred);
    return 1;
  }

  // write to glow.ppm
  write_ppm("glow.ppm", glow, w, h);
  printf("Glow image written to glow.ppm\n");

  free(image);
  free(bright);
  free(blurred);
  free(glow);

  return 0;
}

