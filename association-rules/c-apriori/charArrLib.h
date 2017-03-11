#ifndef CHARARRLIB
#define CHARARRLIB

struct string_array {
  char** array;
  unsigned int length;
  unsigned int size;
};

void push(struct string_array*, char*);
void filter_item(struct string_array*, char*, int(char*, char*));

#endif
