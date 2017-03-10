#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "candidate.h"
#include "charArrLib.c"

void initCandidateTable(struct candidateTable* cTable, unsigned int size) {
  cTable->size = size;
  cTable->length = 0;
  cTable->candidate = (struct candidate*)malloc(sizeof(struct candidate) * size);
}

void addNewCandidate(struct candidateTable* cTable, struct candidate candidate) {
  if (cTable->length == cTable->size) {
    cTable->size *= 2;
    cTable->candidate = (struct candidate*)realloc(cTable->candidate, cTable->size * sizeof(struct candidate));
  }
  cTable->candidate[cTable->length++] = candidate;
}

struct stringArray generateL(struct candidateTable* cTable) {
  struct stringArray nextL;
  struct stringArray itemSet;
  int vote = cTable->candidate[0].level;
  unsigned int i, j;

  for (i = 0; i < cTable->length; i++) {
    for (j = 0; cTable->candidate[i].cList[j]; j++) {
      if (itemSet.length > 0) {
      }
    }
  }

  return nextL;
}
