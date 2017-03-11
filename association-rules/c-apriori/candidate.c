#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "candidate.h"
#include "checkFunction.h"
#include "charArrLib.c"

void init_candidate_table(struct candidate_table* c_table, unsigned int size) {
  c_table->size = size;
  c_table->length = 0;
  c_table->candidate = (struct candidate*)malloc(sizeof(struct candidate) * size);
}

void add_new_candidate(struct candidate_table* c_table, struct candidate candidate) {
  if (c_table->length == c_table->size) {
    c_table->size *= 2;
    c_table->candidate = (struct candidate*)realloc(c_table->candidate, c_table->size * sizeof(struct candidate));
  }
  c_table->candidate[c_table->length++] = candidate;
}

int check_same(char* a, char* b) {
  return strcmp(a, b) == 0 ? 1 : 0;
}

struct stringArray generate_l(struct candidate_table* c_table) {
  struct stringArray next_l;
  struct stringArray item_set;
  int vote = c_table->candidate[0].level;
  unsigned int i, j;

  for (i = 0; i < c_table->length; i++) {
    for (j = 0; c_table->candidate[i].c_list[j]; j++) {
      filter_item(&item_set, c_table->candidate[i].c_list[j], &check_same);
      if (item_set.length > 0) {
        continue;
      }
      push(&item_set, c_table->candidate[i].c_list[j]);
    }
  }



  return next_l;
}
