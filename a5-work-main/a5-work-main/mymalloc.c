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

// size: size of memory
// *next: pointer to next block in list
// free: 1 if free, 0 if in use
typedef struct block {
  size_t size;

  struct block *next;

  int free;
} block_t;

// pointers to the first and last blocks in the list
static block_t *list_start;
static block_t *list_end;

// instantiates a new block of size s using sbrk()
// adds it to the end of the list
// returns a pointer to the header
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


// searches for a free block of size s or greater
// if none found or if the list is empty, return NULL
// returns a pointer to the header
block_t *search_for_free(size_t s) {
  if (list_start == NULL) {
    return NULL;
  }

  block_t *current = list_start;

  while(current != list_end) {
    if (current->size >= s && current->free == 1) {
      return current;
    }
    current = current->next;
  }
  // check the last one as well
  if (current->size >= s && current->free == 1) {
    return current;
  }

  return NULL;
}

// searches for a free block, if none found then creates a new block
// returns a pointer to the memory
void *mymalloc(size_t s) {
  if (s == 0) {
    return NULL;
  }

  block_t *free = search_for_free(s);
  if (free != NULL) {
    free->free = 0;
    debug_printf("Malloc %zu bytes\n", s);
    return free + 1;
  }

  block_t *block = new_block(s);
  if (block == NULL) {
    return NULL;
  }

  debug_printf("Malloc %zu bytes\n", s);
  return block + 1;
}

// uses mymalloc to allocate a block of size nmemb * s and zeroes the values
// returns a pointer to the memory
void *mycalloc(size_t nmemb, size_t s) {
  if (nmemb == 0 || s == 0) {
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

// frees a block given its pointer
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
