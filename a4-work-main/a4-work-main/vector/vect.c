/**
 * Vector implementation.
 *
 * - Implement each of the functions to create a working growable array (vector).
 * - Do not change any of the structs
 * - When submitting, You should not have any 'printf' statements in your vector 
 *   functions.
 *
 * IMPORTANT: The initial capacity and the vector's growth factor should be 
 * expressed in terms of the configuration constants in vect.h
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "vect.h"

/** Main data structure for the vector. */
struct vect {
  char **data;             /* Array containing the actual data. */
  unsigned int size;       /* Number of items currently in the vector. */
  unsigned int capacity;   /* Maximum number of items the vector can hold before growing. */
};

/** Construct a new empty vector. */
vect_t *vect_new() {

  /* [TODO] Complete the function */

  vect_t *v = malloc(sizeof(vect_t));
  assert(v != NULL);

  v->capacity = VECT_INITIAL_CAPACITY;
  v->size = 0;
  v->data = malloc(VECT_INITIAL_CAPACITY * sizeof(char*));
  assert(v->data != NULL);

  return v;
}

/** Delete the vector, freeing all memory it occupies. */
void vect_delete(vect_t *v) {

  /* [TODO] Complete the function */
  assert(v != NULL);

  for(int i = 0; i < v->size; i++) {
    free(v->data[i]);
  }
  free(v->data);
  free(v);
}

/** Get the element at the given index. */
const char *vect_get(vect_t *v, unsigned int idx) {
  assert(v != NULL);
  assert(idx < v->size);

  /* [TODO] Complete the function */

  return v->data[idx];
}

/** Get a copy of the element at the given index. The caller is responsible
 *  for freeing the memory occupied by the copy. */
char *vect_get_copy(vect_t *v, unsigned int idx) {
  assert(v != NULL);
  assert(idx < v->size);

  /* [TODO] Complete the function */

  int len = strlen(v->data[idx]);

  char *copy = malloc(len + 1);
  assert(copy != NULL);
  
  for(int i = 0; i < len + 1; i++) {
    copy[i] = v->data[idx][i];
  }

  return copy;
}
/** Set the element at the given index. */
void vect_set(vect_t *v, unsigned int idx, const char *elt) {
  assert(v != NULL);
  assert(idx < v->size);

  /* [TODO] Complete the function */

  int len = strlen(elt);

  char *copy = malloc(len + 1);
  assert(copy != NULL);
  strcpy(copy, elt);

  free(v->data[idx]);

  v->data[idx] = copy;
}

/** Add an element to the back of the vector. */
void vect_add(vect_t *v, const char *elt) {
  assert(v != NULL);

  /* [TODO] Complete the function */

  if(v->size == v->capacity) {
    v->capacity *= VECT_GROWTH_FACTOR;
    char **data_new = malloc(v->capacity * sizeof(char*));
    assert(data_new != NULL);
    for(int i = 0; i < v->size; i++) {
      data_new[i] = v->data[i];
    }
    data_new[v->size] = malloc(strlen(elt) + 1);
    assert(data_new[v->size] != NULL);
    strcpy(data_new[v->size], elt);
    free(v->data);
    v->data = data_new;
  }else {
    v->data[v->size] = malloc(strlen(elt) + 1);
    assert(v->data[v->size] != NULL);
    strcpy(v->data[v->size], elt);
  }
  v->size++;
}

/** Remove the last element from the vector. */
void vect_remove_last(vect_t *v) {
  assert(v != NULL);

  /* [TODO] Complete the function */

  assert(v->size > 0);
  free(v->data[v->size - 1]);
  v->size--;
}

/** The number of items currently in the vector. */
unsigned int vect_size(vect_t *v) {
  assert(v != NULL);

  /* [TODO] Complete the function */

  return v->size;
}

/** The maximum number of items the vector can hold before it has to grow. */
unsigned int vect_current_capacity(vect_t *v) {
  assert(v != NULL);

  /* [TODO] Complete the function */

  return v->capacity;
}

