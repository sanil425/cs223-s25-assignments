#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "write_ppm.h"

struct thread_data {
  int starti;
  int endi;
  int width;
  int height;
  struct ppm_pixel color;
  struct ppm_pixel* image;
};

void *start(void* userdata) {
  struct thread_data* data = (struct thread_data*) userdata;

  // update color for all pixels within start and end
  for (int i = data->starti; i < data->endi; i++) {
    for (int j = 0; j <data->width;j++) {
      int index = i * data->width + j; // same logic as assignments to compute 1d index using (i,j) coordinates 
      data->image[index] =data->color;  // update color
    }
  }
  return 0;
}

int main(int argc, char** argv) {

  if (argc != 2)
  {
    printf("usage: %s <num>\n", argv[0]);
    exit(0);
  }
  int N = strtol(argv[1], NULL, 10);

  int size = 1024;
  struct ppm_pixel* image = malloc(sizeof(struct ppm_pixel) * size * size);
  struct ppm_pixel* colors = malloc(sizeof(struct ppm_pixel) * N);
  pthread_t* threads = malloc(sizeof(pthread_t) * N);
  struct thread_data* data = malloc(sizeof(struct thread_data) * N);

  for (int i = 0; i < N; i++) {
    // add relevant info to thread data struct
    data[i].width = size;
    data[i].height = size;
    data[i].image = image;

    // divy up rows between N threads
    int chunk = size / N;
    data[i].starti = i * chunk;
    if (i == N - 1) data[i].endi = size;  // if the thread is the last thread, the end index will just be size
    else data[i].endi = (i +1) *chunk; // else its just the start of the thread i+1

    // randomise colour
    data[i].color.red = rand() % 256; 
    data[i].color.green = rand() % 256;
    data[i].color.blue = rand() % 256;

    // to make coherent with sampel output
    // endi-1 as endi excludes the last row so is techincally not in the range of what is being covered by thread i
    printf("Thread is colouring rows %d to %d with colour: %d %d %d\n", data[i].starti, data[i].endi-1,
            data[i].color.red,  data[i].color.green,  data[i].color.blue);
    pthread_create(&threads[i], NULL, start, &data[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  write_ppm("stripes.ppm", image, size, size);
  free(image); // free all the malloc from the base code
  free(colors);
  free(threads);
  free(data);
}

