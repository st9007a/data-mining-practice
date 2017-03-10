#ifndef CANDIDATE
#define CANDIDATE

struct candidate {
  char** cList;
  int count;
};

struct candidateTable {
  struct candidate* candidate;
  unsigned int length;
  unsigned int size;
};

void initCandidateTable(struct candidateTable*, unsigned int);
void addNewCandidate(struct candidateTable*, struct candidate*);
char** generateL(struct candidateTable*);

#endif
