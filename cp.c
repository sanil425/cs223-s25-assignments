#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

#define N 100

// Global variables
pthread_cond_t full;
pthread_cond_t empty;
pthread_mutex_t mux; 
int num_items=0, in=0, out=0, buff[N];

int produce_item() {
    return rand() % 10;
}

void consume_item(int item) {
    printf("Received item: %d\n", item);
}

void* producer(void* usr) {
  // todo
  return NULL;
}

void* consumer(void* usr) {
  // todo
  return NULL;
}

int main() {
  pthread_mutex_init(&mux, NULL);
  pthread_cond_init(&full, NULL);
  pthread_cond_init(&empty, NULL);

  // todo

  pthread_mutex_destroy(&mux);
  pthread_cond_destroy(&full);
  pthread_cond_destroy(&empty);
  return 0;
}

