#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct {
  int thread_id;
  int num_threads;
  int num_files;
  char **filenames;
  char *keyword;
  int *matches;
} ThreadArgs;

void* search_files(void *arg) {
  ThreadArgs* args = (ThreadArgs*) arg; // cast to struct
  int tid = args->thread_id;

  int chunk = args->num_files / args->num_threads; // chunk will be number of files per thread if it was exactly divisble
  int start = tid * chunk; // start index for this thread
  int end = start + chunk; // end index

  if (tid == args->num_threads - 1) {
    end = args->num_files; // last thread takes leftover files
  }
  
  FILE *fp;
  char buffer[1000];

  for (int i = start; i < end; i++) {
    fp = fopen(args->filenames[i], "r");
    if (!fp) {
      printf("Error opening thread");
      continue; // continue to next
    }
  
    // read each line in file
    while (fgets(buffer, sizeof(buffer), fp)) {
      // if the line contains keyword print result with desired info
      if (strstr(buffer, args->keyword)) {
        printf("Thread %d) %s: %s", tid, args->filenames[i], buffer);
        args->matches[tid]++; // increment matches
      }
    }
  fclose(fp);
  }
  return NULL;
}



int main(int argc, char* argv[]) {
  if (argc < 4) {
    printf("error with arguments");
    return 1;
  }

  int t = atoi(argv[1]); // convert string of number of threads into int
  char *keyword = argv[2]; // pointer to keyword string
  int N = argc - 3; // number of files (number of command line arguments - 3)
  char **filenames = &argv[3]; // pointer to start of list of filenames
  printf("Searching %d files for keyword: %s using %d threads\n", N, keyword, t);
  
  pthread_t *threads = malloc(sizeof(pthread_t) * t); // array to hold threads
  long *thread_ids = malloc(sizeof(long) * t); // hold thread ids
  int *thread_matches = malloc(sizeof(int) * t);
  ThreadArgs *thread_args = malloc(sizeof(ThreadArgs) * t); // array of Threadargs for each thread

  // filling each thread
  for (int i = 0; i < t; i++) {
    thread_args[i].thread_id = i;
    thread_args[i].num_threads = t;
    thread_args[i].num_files = N;
    thread_args[i].filenames = filenames;
    thread_args[i].keyword = keyword;
    thread_args[i].matches = thread_matches;
  }

  for (int i = 0; i < t; i++) {
    pthread_create(&threads[i], NULL, search_files, &thread_args[i]);
  }

  // wait for all threads to be done and join
  for (int i = 0; i < t; i++) {
    pthread_join(threads[i], NULL);
  }

  // printing final match summary
  for (int i = 0; i < t; i++) {
    printf("Thread %d found %d lines containing keyword: %s\n", i, thread_matches[i], keyword);
  }

  free(threads);
  free(thread_ids);
  free(thread_matches);
  free(thread_args);

  return 0;
}
