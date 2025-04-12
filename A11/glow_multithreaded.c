/*------------------------------------------------
 * Author: Sanil Kagalwala
 * Date: 11th April 2025
 * File: glow.c
 * Description: Applies a glow filter to a PPM image using multiple threads.
 *------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <getopt.h>

struct ppm_pixel* bright_areas(struct ppm_pixel* image, int w, int h, int threshold);
struct ppm_pixel* blur_image(struct ppm_pixel* image, int w, int h, int box_size);
struct ppm_pixel* add_glow(struct ppm_pixel* image, struct ppm_pixel* blur_image, int w, int h);

typedef struct {
  int thread_id;               
  int start_row; // inclusive
  int end_row;   // exclusive    
  int width;
  int height;
  int threshold;
  int blursize;
  struct ppm_pixel* image;
  struct ppm_pixel* glow;   
} thread_args;


void* thread_function(void* arg) {
  thread_args* args = (thread_args*) arg;

  int w = args->width;
  int start = args->start_row;
  int end = args->end_row;
  int threshold = args->threshold;
  int blursize = args->blursize;
  struct ppm_pixel* image = args->image;
  struct ppm_pixel* output = args->glow;

  // partial height = number of rows this thread is responsible for
  int partial_h = end - start;

  // allocate memory for this thread's partial image slice
  struct ppm_pixel* partial_image = malloc(sizeof(struct ppm_pixel) * w * partial_h);
  if (!partial_image) {
    fprintf(stderr, "Thread %d: Failed to allocate partial image\n", args->thread_id);
    pthread_exit(NULL);
  }

  // copy rows this thread is responsible for into partial_image
  for (int y = start; y < end; y++) {
    for (int x = 0; x < w; x++) {
      // (y - start) shifts row index so row 0 in slice is the top of this thread's work
      partial_image[(y - start) * w + x] = image[y * w + x];
    }
  }

  // apply helper functions on this thread's slice
  struct ppm_pixel* bright = bright_areas(partial_image, w, partial_h, threshold);
  struct ppm_pixel* blurred = blur_image(bright, w, partial_h, blursize);
  struct ppm_pixel* partial_glow = add_glow(partial_image, blurred, w, partial_h);

  // copy the result (partial_glow) back into the correct position in shared output
  for (int y = start; y < end; y++) {
    for (int x = 0; x < w; x++) {
      output[y * w + x] = partial_glow[(y - start) * w + x];
    }
  }

  // clean up memory
  free(partial_image);
  free(bright);
  free(blurred);
  free(partial_glow);

  pthread_exit(NULL);
}

// === Main Function ===
int main(int argc, char* argv[]) 
{
  // default settings
  int N = 4;
  int threshold = 200;
  int blursize = 24;
  const char* filename = "earth-small.ppm";

  // parse command line arguments
  int opt;
  while ((opt = getopt(argc, argv, ":N:t:b:f:")) != -1) {
    switch (opt) {
      case 'N': N = atoi(optarg); break;
      case 't': threshold = atof(optarg); break;
      case 'b': blursize = atof(optarg); break;
      case 'f': filename = optarg; break;
      case '?': 
        printf("usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n", argv[0]); 
        return 1;
    }
  }

  // read input image
  int w, h;
  struct ppm_pixel* image = read_ppm(filename, &w, &h);
  if (!image) {
    fprintf(stderr, "Error: Could not read image %s\n", filename);
    return 1;
  }

  // allocate space for final output image
  struct ppm_pixel* glow = malloc(sizeof(struct ppm_pixel) * w * h);
  if (!glow) {
    fprintf(stderr, "Error: Could not allocate memory for output image\n");
    free(image);
    return 1;
  }

  // divide image into N slices for each thread
  int chunk = h / N;

  // create threads and assign arguments
  pthread_t* threads = malloc(sizeof(pthread_t) * N);
  thread_args* args = malloc(sizeof(thread_args) * N);

  for (int i = 0; i < N; i++) {
    args[i].thread_id = i;
    args[i].start_row = i * chunk;
    args[i].end_row = (i == N - 1) ? h : (i + 1) * chunk; // last thread takes remaining rows
    args[i].width = w;
    args[i].height = h;
    args[i].threshold = threshold;
    args[i].blursize = blursize;
    args[i].image = image;
    args[i].glow = glow;

    pthread_create(&threads[i], NULL, thread_function, &args[i]);
  }

  // wait for all threads to finish
  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  // write final glow image to file
  write_ppm("glow.ppm", glow, w, h);
  printf("Glow image written to glow.ppm\n");

  free(threads);
  free(args);
  free(image);
  free(glow);

  return 0;
}




// helper functions

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

