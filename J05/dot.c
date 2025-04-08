#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 100000
#define NUM_THREADS 4
int sums_array[4];

struct thread_data {
  int start_index;
  int end_index;
  int *v;
  int *u;
  int partial_sum;
};

int v[SIZE];
int u[SIZE];
struct thread_data data[NUM_THREADS];

void *compute_dot(void *userdata) {
  struct thread_data *data = (struct thread_data *) userdata;
  int sum = 0;
  for (int i = data->start_index; i < data->end_index; i++) {
    sum += data->v[i] * data->u[i];
  }
  data->partial_sum = sum;
  return NULL;
}

int main(int argc, char *argv[]) {
  srand(time(0));
  int dotproduct = 0;

  for (int i = 0; i < SIZE; i++) {
    v[i] = rand() % 1000 - 500;
    u[i] = rand() % 1000 - 500;
    dotproduct += u[i] * v[i];
  }
  printf("Ground truth dot product: %d\n", dotproduct);

  // our solution here
  pthread_t threads[NUM_THREADS];
  int chunk = SIZE / NUM_THREADS;

  for (int i = 0; i < NUM_THREADS; i++) {
    data[i].start_index = i * chunk;
    data[i].end_index = (i == NUM_THREADS - 1) ? SIZE : (i + 1) * chunk;
    data[i].v = v;
    data[i].u = u;
    data[i].partial_sum = 0;
    pthread_create(&threads[i], NULL, compute_dot, &data[i]);
  }

  int thread_dotproduct = 0;
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
    thread_dotproduct += data[i].partial_sum;
  }

  printf("Test with 4 threads\n");
  printf("Answer with threads: %d\n", thread_dotproduct);
  return 0;
}
