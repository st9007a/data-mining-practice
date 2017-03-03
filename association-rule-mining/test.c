#include <stdio.h>
#include <stdlib.h>
#include "fpTree.c"

int main(int argc, char** argv) {

  // add to header table test
  struct array ht;
  newArray(&ht, 1);
  addToHeaderTable(&ht, "1 2 1 4");
  addToHeaderTable(&ht, "1 3 4 6");
  addToHeaderTable(&ht, "2 1 3 5");
  addToHeaderTable(&ht, "1 3 1 1");
  addToHeaderTable(&ht, "3 2 2 6");

  int j;
  for(j=0;j<ht.used;j++) {
    printf("%s : %lu\n", ht.items[j].item, ht.items[j].frequency);
  }

  return 0;


  // quick sort test
  struct array arr;
  struct frequencyItem f1;
  struct frequencyItem f2;
  struct frequencyItem f3;
  struct frequencyItem f4;
  struct frequencyItem f5;
  struct frequencyItem f6;
  struct frequencyItem f7;
  newArray(&arr, 3);
  f1.frequency = 10;
  f2.frequency = 2;
  f3.frequency = 20;
  f4.frequency = 5;
  f5.frequency = 12;
  f6.frequency = 1;
  f7.frequency = 1;
  push(&arr, f1);
  push(&arr, f2);
  push(&arr, f3);
  push(&arr, f4);
  push(&arr, f5);
  push(&arr, f6);
  push(&arr, f7);

  arr = quickSort(arr);

  printf("for each\n");

  int i;
  for (i = 0; i < arr.used; i++) {
    printf("arr %lu\n", arr.items[i].frequency);
  }

  return 0;
}
