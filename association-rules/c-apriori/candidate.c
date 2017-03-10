#include <stdio.h>
#include <stdlib.h>
#include "candidate.h"

void initCandidateTable(struct candidateTable* cTable, unsigned int size) {
  cTable->size = size;
  cTable->length = 0;
  cTable->candidate = (struct candidate*)malloc(sizeof(struct candidate) * size);
}

void addNewCandidate(struct candidateTable* cTable, struct candidate* candidate) {
  if (cTable->length == cTable->size) {
    cTable->size *= 2;
    cTable->candidate = (struct candidate*)realloc(cTable->candidate, cTable->size * sizeof(struct candidate));
  }
  cTable->candidate[cTable->length++] = *candidate;
}

char** generateL(struct candidateTable* cTable) {
  char** nextL;

}
