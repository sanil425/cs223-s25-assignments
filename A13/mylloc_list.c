/***************************************************
 * mylloc_list.c
 * Author: Sanil Kagalwala
 * Date: 23rd April 2025
 * Implementation fo memepry allocator that uses a 
 * linked list to manage the memory allocation.
 ***************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int used;
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  // TODO: Implement malloc with a free list (See reading for details)
  if (size == 0) return NULL;

  struct chunk* current = flist;
  struct chunk* prev = NULL;

  while (current != NULL) {
    if (current->size >= size) {
      if (prev != NULL) {
        prev->next = current->next;
      } 
      else { // when prev doesn't exist as current is the head 
        flist = current->next; // move flist to next chunk
      }
      current->used = size;
      return (void*)(current + 1); // return ptr just after current head
    }
    prev = current;
    current = current->next;
  }

  void* memory = sbrk(size + sizeof(struct chunk)); // requests block of mem large enough for size and chunk header
  if (memory == (void*) -1) return NULL; // sbrk call failed
  else {
    struct chunk *cnk = (struct chunk*) memory; // cast memory to pointer of struct chunk
    // populate cnk with data
    cnk->size = size;
    cnk->used = size;
    cnk->next = NULL;
    return (void *)(cnk + 1); // points to area right after cnk, to users data area
  }

  return NULL;
}

void free(void *memory) {
  // TODO: Implement malloc with a free list (See reading for details)
  if (memory != NULL) {
    // step back one chunk from user memory to access desired chunk
    struct chunk *cnk = (struct chunk *)memory - 1;
    cnk->next = flist; // add to flist linked list
    flist = cnk;
  }
  return;
}
