#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fpTree.h"
#include "array.c"

char** parseLine(char* line, int* listLen) {
  char** list;
  int i = 0;
  char* token = " ";
  char* item;
  char* cp = malloc(strlen(line) + 1);
  list = malloc(strlen(line) / sizeof(char) * sizeof(char*));

  strcpy(cp, line);
  item = strtok(cp, token);

  while (item != NULL) {
    char* el = malloc(strlen(item));
    strcpy(el, item);
    list[i++] = el;
    item = strtok(NULL, token);
  }
  list = realloc(list, i * sizeof(char*));
  *listLen = i;
  return list;
}

void addToHeaderTable(struct array* headerTable, char** list, int listLen, int times) {
  int i;
  for (i = 0; i < listLen; i++) {
    int j;
    int flag = 0;
    for (j = 0; j < headerTable->used; j++) {
      if (strcmp(headerTable->items[j].item, list[i]) == 0) {
        headerTable->items[j].frequency += times;
        flag++;
        break;
      }
    }
    if (flag == 0) {
      struct frequencyItem f = { list[i], times, NULL };
      push(headerTable, f);
    }
  }
}

void removeNotSupportItems(struct array* headerTable, char** list, int* listLen) {
  int i;
  int len = 0;

  for (i = 0; i < *listLen; i++) {
    int j;
    for (j = 0; j < headerTable->used; j++) {
      if (strcmp(list[i], headerTable->items[j].item) == 0) {
        char* tmp = list[i];
        list[i] = list[len];
        list[len++] = tmp;
        break;
      }
    }
  }

  *listLen = len;
  list = realloc(list, (*listLen) * sizeof(char*));
}

void sortList(struct array* headerTable, char** list, int listLen) {
  int i, j, pos = 0;
  for (i = 0; i < headerTable->used; i++) {
    for (j = 0; j < listLen; j++) {
      if (strcmp(headerTable->items[i].item, list[j]) == 0) {
        char* tmp = list[pos];
        list[pos++] = list[j];
        list[j] = tmp;
        break;
      }
    }
  }
}

void buildLink(struct array* headerTable, struct fpTree* node) {
  printf("[build link] \n");
  int i;
  for (i = 0; i < headerTable->used; i++) {
    if (strcmp(headerTable->items[i].item, node->item) == 0) {
      if (headerTable->items[i].link == NULL) {
        headerTable->items[i].link = node;
        break;
      }
      else {
        struct fpTree* linkTo = headerTable->items[i].link;
        while (linkTo->link != NULL) {
          linkTo = linkTo->link;
        }
        linkTo->link = node;
        break;
      }
    }
  }
}

void insertToFPTree(struct array* headerTable, struct fpTree* rootNode, char** list, int listLen, int times) {
  if (listLen <= 0) {
    return;
  }

  int i;
  printf("------------------------------\ninsert\n");
  struct fpTree* node = rootNode;
  for (i = listLen - 1; i >= 0; i--) {
    printf("list: %s, \n", list[i]);
    int j, pos;
    int isExist = 0;
    for (j = 0; j < node->childrenLen; j++) {
      if (strcmp(node->children[j].item, list[i]) == 0) {
        pos = j;
        node->children[j].count += times;
        isExist++;
        break;
      }
    }
    if (!isExist) {
      if ((node->childrenLen | node->childrenSize) == 0) {
        node->childrenSize = 1;
        node->children = malloc(sizeof(struct fpTree));
      }
      else if (node->childrenLen == node->childrenSize) {
        node->childrenSize *= 2;
        node->children = realloc(node->children, sizeof(struct fpTree) * node->childrenSize);
      }
      struct fpTree child = {list[i], times, 0, 0, NULL, NULL, NULL};
      child.parent = malloc(sizeof(struct fpTree));
      *child.parent = *node;
      node->children[node->childrenLen] = child;
      pos = node->childrenLen++;
      buildLink(headerTable, &node->children[pos]);
    }
    node = &node->children[pos];
    printf("f: %lu\n", node->count);
  }
}

char** getPrefixPath(struct fpTree* base, int* listLen) {
  struct fpTree* pNode = base;
  char** list;
  int i = 0;
  list = malloc(*listLen * sizeof(char*));
  while (pNode->parent != NULL) {
    list[i++] = pNode->item;
    pNode = pNode->parent;
  }
  *listLen = i;
  list = *listLen == 0 ? NULL : list;
  return list;
}

void trimPrefixPath(struct array* ht, char** list, int* listLen) {
  int i, j;
  for (i = 0; i < *listLen; i++) {
    int isExist = 0;
    for (j = 0; j < ht->used; j++) {
      if (strcmp(list[i], ht->items[j].item) == 0) {
        isExist = j;
        break;
      }
    }
    if (!isExist) {
      for (j = isExist; j < *listLen; j++) {
        list[isExist] = list[isExist + 1];
      }
      *listLen--;
    }
  }
}

void miningTree(struct array* headerTable, struct fpTree* rootNode, int countOfMinSup, float minConf) {
  if (rootNode->children ==  NULL) {
    //handle null
    printf("empty tree\n");
    return;
  }

  int i;
  for (i = 0; i < headerTable->used; i++) {
    struct array subHT;
    struct fpTree subTree = fpTreeDefault;
    struct fpTree* linkTo = headerTable->items[i].link;
    int j;


    ////suffix set
    //printf("suffix\n");
    //if (suffix == NULL) {
    //  suffix = malloc(sizeof(char*));
    //  suffix[0] = headerTable->items[i].item;
    //  suffix[1] = NULL;//? magic bug
    //}
    //else {
    //  for (j = 0; suffix[j] != NULL; j++) {}
    //  suffix = realloc(suffix, sizeof(char*) * (j + 1));
    //  suffix[j] = headerTable->items[i].item;
    //}

    //build header table
    printf("header table\n");
    newArray(&subHT, 1);
    while (linkTo != NULL) {
      char** list = NULL;
      int times = linkTo->count;
      int listLen = headerTable->used;
      list = getPrefixPath(linkTo, &listLen);
      printf("prefix ---\n");
      printf("prefix times %d\n", times);
      for (j = 0; j < listLen; j++) {
        printf("prefix %s\n", list[j]);
      }
      addToHeaderTable(&subHT, list, listLen, times);
      linkTo = linkTo->link;
    }

    subHT = quickSort(subHT);
    for (j = 0; j < subHT.used; j++) {
      printf("item: %s, count: %d\n", subHT.items[j].item, subHT.items[j].frequency);
    }

    return;
    for (j = 0; j < subHT.used; j++) {
      if (subHT.items[j].frequency >= countOfMinSup) {
        removeMultiItems(&subHT, 0, j - 1);
        break;
      }
    }

    // build fp tree
    printf("fp tree\n");
    linkTo = headerTable->items[i].link;
    while (linkTo != NULL) {
      char** list = NULL;
      int times = linkTo->count;
      int listLen = subHT.used;
      list = getPrefixPath(linkTo, &listLen);
      //! buid conditional sub tree
      linkTo = linkTo->link;
    }

    //find frequency set

    miningTree(&subHT, &subTree, countOfMinSup, minConf);
  }
}
