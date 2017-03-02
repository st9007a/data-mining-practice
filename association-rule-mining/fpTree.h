#ifndef FPTREE
#define FPTREE

struct fpTree {
  char* item;
  int count;
  struct fpTree* parent;
  struct fpTree* children;
  struct fpTree* link;
};

struct frequencyItem {
  char* item;
  int frequency;
  struct fpTree* link;
};

void addToHeaderTable(struct frequencyItem*, char*);
struct frequencyItem* sortHeaderTable(struct frequencyItem*, int);
struct frequencyItem* concatStruct(struct frequencyItem*, struct frequencyItem*);

#endif
