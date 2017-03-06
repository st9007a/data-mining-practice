#ifndef FPTREE
#define FPTREE

#include "array.h"

struct fpTree {
  char* item;
  size_t count;
  size_t childrenLen;
  size_t childrenSize;
  struct fpTree* parent;
  struct fpTree* children;
  struct fpTree* link;
} fpTreeDefault = { "", 1, 0, 0, NULL, NULL, NULL };

struct frequencyItem {
  char* item;
  size_t frequency;
  struct fpTree* link;
};

char** parseLine(char*, int*);
void addToHeaderTable(struct array*, char**, int, int);
void removeNotSupportItems(struct array*, char**, int*);
void sortList(struct array*, char**, int);
void buildLink(struct array*, struct fpTree*);
void insertToFPTree(struct array*, struct fpTree*, char**, int, int);

char** getPrefixPath(struct fpTree*, int*);
void trimPrefixPath(struct array*, char**);
void swapPrefixPath(char**);
void miningTree(struct array*, struct fpTree*, int ,float);

#endif
