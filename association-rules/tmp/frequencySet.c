#include "frequencySet.h"

void pushToPrefix(struct frequencySet* set, char* item) {
  if (set->prefixSize == 0) {
    set->prefix = malloc(sizeof(char));
    set->prefixSize++;
  }
  else if (set->prefixLen == set->prefixSize) {
    set->prefixSize *= 2;
    set->prefix = realloc(set->prefix, sizeof(char) * set->prefixSize);
  }
  set->prefix[set->prefixLen++] = item;
}

void pushToSuffix(struct frequencySet* set, char* item) {
  if (set->suffixSize == 0) {
    set->suffix = malloc(sizeof(char));
    set->suffixSize++;
  }
  else if (set->suffixLen == set->suffixSize) {
    set->suffixSize *= 2;
    set->suffix = realloc(set->suffix, sizeof(char) * set->suffixSize);
  }
  set->prefix[set->suffixLen++] = item;
}
