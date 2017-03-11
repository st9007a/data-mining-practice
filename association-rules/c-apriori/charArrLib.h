#ifndef CHARARRLIB
#define CHARARRLIB

struct stringArray {
  char** array;
  unsigned int length;
  unsigned int size;
};

void push(struct stringArray*, char*);
void filter_item(struct stringArray*, char*, int(char*, char*));

#endif
