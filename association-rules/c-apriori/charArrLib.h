#ifndef CHARARRLIB
#define CHARARRLIB

#include <stdlib.h>

struct string_array {
  char** array;
  size_t length;
  size_t size;
};

void init_string_array(struct string_array*, size_t);
void push(struct string_array*, char*);
void filter_item(struct string_array*, char*, int(char*, char*));

#endif
