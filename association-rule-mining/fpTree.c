#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fpTree.h"
#include "array.c"

void addToHeaderTable(struct array* headerTable, char* line) {
  char* token = " ";
  char* item;
  char* cp = malloc(strlen(line) + 1);

  strcpy(cp, line);
  item = strtok(cp, token);

  while (item != NULL) {
    int i;
    int flag = 0;
    char* el = malloc(strlen(item));
    strcpy(el, item);
    for (i = 0; i < headerTable->used; i++) {
      if (strcmp(headerTable->items[i].item, el) == 0) {
        headerTable->items[i].frequency++;
        flag++;
        break;
      }
    }
    if (flag == 0) {
      struct frequencyItem f;
      f.frequency = 1;
      f.item = el;
      push(headerTable, f);
    }
    item = strtok(NULL, token);
  }
}

void removeNotSupportItems(struct array* headerTable, char* line, char** list, int* listLen) {
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
}

void sortList(struct array* headerTable, char** list, int listLen) {
  int i, j, pos = 0;
  for (i = 0; i < listLen; i++) {
    for (j = 0; j < headerTable->used; j++) {
      if (strcmp(headerTable->items[j].item, list[i]) == 0) {
        char* tmp = list[pos];
        list[pos++] = list[i];
        list[i] = tmp;
        break;
      }
    }
  }
}

void insertToFPTree(struct fpTree* rootNode, char** list, int listLen) {
  int i;
  struct fpTree* node = rootNode;
  for (i = 0; i < listLen; i++) {
    int j, pos;
    int flag = 0;
    for (j = 0; j < node->childrenLen; j++) {
      if (strcmp(node->children[j].item, list[i]) == 0) {
        pos = j;
        node->children[j].count++;
        flag++;
        break;
      }
    }
    if (flag) {
      if (node->childrenLen | node->childrenSize == 0) {
        node->childrenSize = 1;
        node->children = malloc(sizeof(struct fpTree));
      }
      else if (node->childrenLen == node->childrenSize) {
        node->childrenSize *= 2;
        node->children = realloc(node->children, sizeof(struct fpTree) * node->childrenSize);
      }
      struct fpTree child;
      child.item = list[i];
      child.count = 1;
      child.parent = node;
      node->children[node->childrenLen++] = child;
      pos = node->childrenLen - 1;
    }
    node = &node->children[pos];
    //handle link
  }
}
