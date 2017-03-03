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

