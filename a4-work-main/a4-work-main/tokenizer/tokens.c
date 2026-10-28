/* TODO: Provide implementations of your tokenize function here */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../vector/vect.h"
#include "tokens.h"

// special token?
int is_special(char ch) {
  return ch == '(' || ch == ')' || ch == '<' || ch == '>' || ch == ';' || ch == '|';
}

int is_whitespace(char ch) {
  return ch == ' ' || ch == '\t' || ch == '\n';
}

// read next word from input into output
int read_word(const char *input, char *output) {
  int i = 0;
  while(input[i] != '\0' && !is_whitespace(input[i]) && !is_special(input[i]) && input[i] != '"') {
    output[i] = input[i];
    i++;
  }
  output[i] = '\0';

  return i;
}

// read quoted string into output, without quotes
// return num of characters
int read_quoted(const char *input, char *output) {
  int i = 1;
  int j = 0;
  while(input[i] != '\0' && input[i] != '"') {
    output[j] = input[i];
    i++;
    j++;
  }
  output[j] = '\0';

  if(input[i] == '"') {
    i++;
  }

  return i;
}

// turn input into a vector of tokens
vect_t *tokenize(const char *input) {
  assert(input != NULL);

  vect_t *tokens = vect_new();

  // no token can be longer than the input itself
  char *buf = malloc(strlen(input) + 1);
  assert(buf != NULL);

  int i = 0;
  while(input[i] != '\0') {
    if(is_whitespace(input[i])) {
      i++;
      continue;
    }

    if(is_special(input[i])) {
      buf[0] = input[i];
      buf[1] = '\0';
      vect_add(tokens, buf);
      i++;
      continue;
    }

    if(input[i] == '"') {
      i += read_quoted(&input[i], buf);
      vect_add(tokens, buf);
      continue;
    }

    i += read_word(&input[i], buf);
    vect_add(tokens, buf);
  }

  free(buf);

  return tokens;
}