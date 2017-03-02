#ifndef FPTREE
#define FPTREE

struct fpTree {
  char* item;
  size_t count;
  struct fpTree* parent;
  struct fpTree* children;
  struct fpTree* link;
};

struct frequencyItem {
  char* item;
  size_t frequency;
  struct fpTree* link;
};

void addToHeaderTable(struct frequencyItem*, char*);
struct frequencyItem* sortHeaderTable(struct frequencyItem*, int);
struct frequencyItem* concatStruct(struct frequencyItem*, struct frequencyItem*);

#endif
