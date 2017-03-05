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
  printf("[build link] ");
  int i;
  for (i = 0; i < headerTable->used; i++) {
    if (strcmp(headerTable->items[i].item, node->item) == 0) {
      if (headerTable->items[i].link == NULL) {
        headerTable->items[i].link = node;
        break;
      }
      else {
        struct fpTree* linkTo = headerTable->items[i].link;
        int j = 0;
        while (linkTo->link != NULL) {
          linkTo = linkTo->link;
          j++;
        }
        linkTo->link = node;
        printf("%d ", j);
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
    printf("list: %s, ", list[i]);
    int j, pos;
    int isExist = 0;
    struct fpTree child;
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
      child.item = list[i];
      child.count = times;
      child.childrenLen = 0;
      child.childrenSize = 0;
      child.parent = node;
      child.children = NULL;
      child.link = NULL;
      node->children[node->childrenLen] = child;
      pos = node->childrenLen++;
      buildLink(headerTable, &child);
    }
    node = &node->children[pos];
    printf("f: %lu\n", node->count);
  }
}

char** getPrefixPath(struct fpTree* base, int* times, int* listLen) {
  struct fpTree* pNode = base;
  char** list = malloc(*listLen * sizeof(char*));
  int i = 0;
  *times = base->count;
  while (pNode->parent != NULL) {
    list[i++] = pNode->item;
    pNode = pNode->parent;
  }
  *listLen = i;
  list = realloc(list, *listLen * sizeof(char*));
  return list;
}

void miningTree(struct array* headerTable, struct fpTree* rootNode, int countOfMinSup, float minConf, char** suffix) {
  if (rootNode->children ==  NULL) {
    //handle null
    return;
  }

  int i;
  for (i = 0; i < headerTable->used; i++) {
    struct array subHT;
    struct fpTree subTree;
    struct fpTree* linkTo = headerTable->items[i].link;
    int j;

    //suffix set
    if (suffix == NULL) {
      suffix = malloc(sizeof(char*));
      suffix[0] = headerTable->items[i].item;
    }
    else {
      for (j = 0; suffix[j] != NULL; j++) {}
      suffix = realloc(suffix, sizeof(char*) * (j + 1));
      suffix[j] = headerTable->items[i].item;
    }

    //build header table
    newArray(&subHT, 1);
    while (linkTo != NULL) {
      char** list = NULL;
      int times;
      int listLen = headerTable->used;
      list = getPrefixPath(linkTo, &times, &listLen);
      addToHeaderTable(&subHT, list, listLen, times);
    }
    subHT = quickSort(subHT);

    for (j = 0; j < subHT.used; j++) {
      if (subHT.items[j].frequency >= countOfMinSup) {
        removeMultiItems(&subHT, 0, j - 1);
        break;
      }
    }

    // build fp tree
    linkTo = headerTable->items[i].link;
    while (linkTo != NULL) {
      char** list;
      int times;
      int listLen = subHT.used;
      list = getPrefixPath(linkTo, &times, &listLen);
      removeNotSupportItems(&subHT, list, &listLen);
      sortList(&subHT, list, listLen);
      insertToFPTree(&subHT, &subTree, list, listLen, times);
    }

    //find frequency set
    printf("build\n");

    miningTree(&subHT, &subTree, countOfMinSup, minConf, suffix);
  }
}
