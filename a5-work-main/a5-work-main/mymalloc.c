#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#include <malloc.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
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

  if (list_start == NULL) {
    block_t *block = new_block(s);
    if (block == NULL) {
      return NULL;
    }

    debug_printf("Malloc %zu bytes\n", s);
    return block + 1;
  }

  block_t *current = list_start;

  while(current != list_end) {
    if (current->size >= s && current->free == 1) {
      current->free = 0;
      debug_printf("Malloc %zu bytes\n", s);
      return current + 1;
    }
    current = current->next;
  }
  // check the last one as well
  if (current->size >= s && current->free == 1) {
    current->free = 0;
    debug_printf("Malloc %zu bytes\n", s);
    return current + 1;
  }

  block_t *block = new_block(s);
  if (block == NULL) {
    return NULL;
  }

  debug_printf("Malloc %zu bytes\n", s);
  return block + 1;
}

void *mycalloc(size_t nmemb, size_t s) {
  if (nmemb == 0) {
    return NULL;
  }

  if (s > SIZE_MAX / nmemb) {
    return NULL;
  }

  block_t *block = mymalloc(nmemb * s);
  if (block == NULL) {
    return NULL;
  }
  block = memset(block, 0, nmemb * s);

  debug_printf("Calloc %zu bytes\n", nmemb * s);

  return block;
}

void myfree(void *ptr) {
  if (ptr == NULL) {
    return;
  }

  block_t *block = ptr;
  block = block - 1;
  assert(block->free != 1);

  size_t size = block->size;

  block->free = 1;

  debug_printf("Freed %zu bytes\n", size);
}
