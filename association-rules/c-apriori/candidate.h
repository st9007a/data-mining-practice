#ifndef CANDIDATE
#define CANDIDATE

struct candidate {
  char** cList;
  int count;
  int level;
};

struct candidateTable {
  struct candidate* candidate;
  unsigned int length;
  unsigned int size;
};

void initCandidateTable(struct candidateTable*, unsigned int);
void addNewCandidate(struct candidateTable*, struct candidate);
struct stringArray generateL(struct candidateTable*);

#endif
