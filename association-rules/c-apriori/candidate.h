#ifndef CANDIDATE
#define CANDIDATE

#include <stdlib.h>
#include "charArrLib.h"

struct candidate{
  struct string_array c_list;
  int count;
  int level;
};

struct candidate_table {
  struct candidate* candidate;
  size_t length;
  size_t size;
};

void init_candidate_table(struct candidate_table*, size_t);
void add_new_candidate(struct candidate_table*, struct candidate);
struct string_array generate_l(struct candidate_table*);

#endif
