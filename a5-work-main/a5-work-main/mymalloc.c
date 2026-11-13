#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#include <malloc.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

// Include any other headers we need here

// NOTE: You should NOT include <stdlib.h> in your final implementation.
// malloc.h turns every call to malloc/calloc/free in this file into a call
// to mymalloc/mycalloc/myfree, so calling them here would recurse forever.

#include <debug.h> // definition of debug_printf

typedef struct block {
  size_t size;

  struct block *next;

  int free;
} block_t;

static block_t *list_start;
static block_t *list_end;

block_t *new_block(size_t s) {
  block_t *block = sbrk(sizeof(block_t) + s);
  if (block == (void *) -1) {
    return NULL;
  }
  block->size = s;
  block->next = NULL;
  block->free = 0;
  if (list_end != NULL) {
    list_end->next = block;
    list_end = block;
  } else {
    list_start = block;
    list_end = block;
  }
  return block;
}

void *mymalloc(size_t s) {
  if (s == 0) {
    return NULL;
  }

  block_t *block = new_block(s);
  if (block == NULL) {
    return NULL;
  }
  
  debug_printf("Malloc %zu bytes\n", s);

  return block + 1;
}

void *mycalloc(size_t nmemb, size_t s) {

  void *p = NULL; // TODO: get the memory from mymalloc, then set it to 0

  if (!p) {
    // We are out of memory
    // if we get NULL back from mymalloc
  }
  debug_printf("Calloc %zu bytes\n", nmemb * s);

  return p;
}

void myfree(void *ptr) {
  size_t size = 0; // TODO: the size stored in ptr's block header

  // TODO: mark ptr's block as free

  debug_printf("Freed %zu bytes\n", size);
}
