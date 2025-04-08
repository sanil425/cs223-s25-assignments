#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100
#define NUM_THREADS 4
#define CHUNK (SIZE / NUM_THREADS)

// your code here
struct thread_data {
  int submatrix[CHUNK][SIZE];
  int *vector;
  int *result;
  int offset;  // where to start writing in result array
};


void *matrix_vector_product(void *arg) {
  struct thread_data *data = (struct thread_data *) arg;
  for (int i = 0; i < CHUNK; i++) {
    int sum = 0;
    for (int j = 0; j < SIZE; j++) {
      sum += data->submatrix[i][j] * data->vector[j];
    }
    data->result[data->offset + i] = sum;
  }
  return NULL;
}


int main(int argc, char *argv[]) {
  srand(time(0));

  int M[SIZE*SIZE];
  int u[SIZE];
  int result[SIZE];
  int result_threads[SIZE];
   
  for (int i = 0; i < SIZE; i++) {
    u[i] = rand() % 10 - 5;
    result[i] = 0;
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int value = rand() % 10 - 5;
      M[i*SIZE + j] = value;
      result[i] += value * u[j];
    }
  }

  // TODO: Implement your thread solution here
  printf("Test with 4 threads\n");

  pthread_t threads[NUM_THREADS];
  struct thread_data thread_args[NUM_THREADS];

  // copy 25 row sub matrix into thread data
  for (int t = 0; t < NUM_THREADS; t++) {
    int base = t * CHUNK; // where on M to start from
    for (int i = 0; i < CHUNK; i++) {
      for (int j = 0; j < SIZE; j++) {
        thread_args[t].submatrix[i][j] = M[(base + i) * SIZE + j];
        // convert into 2d array from 1d array M
      } 
    }
    thread_args[t].vector = u;
    thread_args[t].result = result_threads;
    thread_args[t].offset = base;
    pthread_create(&threads[t], NULL, matrix_vector_product, &thread_args[t]);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  int error = 0;
  for (int i = 0; i < SIZE; i++) {
    error += abs(result[i] - result_threads[i]);
  }
  printf("Error between ground truth and multithreaded version: %d\n", error);

  return 0;
}
