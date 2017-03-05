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

void addToHeaderTable(struct array* headerTable, char** list, int listLen) {
  int i;
  for (i = 0; i < listLen; i++) {
    int j;
    int flag = 0;
    for (j = 0; j < headerTable->used; j++) {
      if (strcmp(headerTable->items[j].item, list[i]) == 0) {
        headerTable->items[j].frequency++;
        flag++;
        break;
      }
    }
    if (flag == 0) {
      struct frequencyItem f = { list[i], 1, NULL };
      push(headerTable, f);
    }
  }
}

char** removeNotSupportItems(struct array* headerTable, char* line, int* listLen) {
  char** list;
  char* token = " ";
  char* item;
  char* cp = malloc(strlen(line) + 1);
  *listLen = 0;

  strcpy(cp, line);
  item = strtok(cp, token);
  list = malloc(strlen(line) * sizeof(char*));
  while (item != NULL) {
    int i;
    char* el = malloc(strlen(item));
    strcpy(el, item);
    for (i = 0; i < headerTable->used; i++) {
      if (strcmp(el, headerTable->items[i].item) == 0) {
        list[(*listLen)++] = el;
        break;
      }
    }
    item = strtok(NULL, token);
  }

  list = realloc(list, (*listLen) * sizeof(char*));
  return list;
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
      struct fpTree* linkTo = headerTable->items[i].link;
      while (linkTo != NULL) {
        linkTo = linkTo->link;
      }
      linkTo = node;
      break;
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
      struct fpTree child = { list[i], times, 0, 0, node, NULL, NULL, 0 };
      node->children[node->childrenLen] = child;
      pos = node->childrenLen++;
      buildLink(headerTable, &node->children[pos]);
    }
    node = &node->children[pos];
    printf("f: %lu\n", node->count);
  }
}

