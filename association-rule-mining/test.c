#include <stdio.h>
#include <stdlib.h>
#include "fpTree.c"

int main(int argc, char** argv) {

  //reference test
  struct fpTree ft = {"a", 1, 0 ,0};
  struct fpTree fr = ft;
  ft.item = "ss";
  printf("%s\n", fr.item);
  return 0;

  //logic
  int a1 = 4;
  int b1 = 6;
  printf("%d\n", a1|b1);
  return 0;

  //change test
  char* a = "111";
  char* b = "222";
  char* tmp;

  tmp = a;
  a = b;
  b = tmp;
  printf("a : %s, b : %s\n", a, b);
  return 0;

  //remove
  struct array ra;
  newArray(&ra, 1);
  struct frequencyItem r1;
  struct frequencyItem r2;
  struct frequencyItem r3;
  struct frequencyItem r4;

  r1.item = "1";
  r2.item = "2";
  r3.item = "3";
  r4.item = "4";

  push(&ra, r1);
  push(&ra, r2);
  push(&ra, r3);
  push(&ra, r4);

  removeMultiItems(&ra, 1, 2);

  int r;
  for (r = 0;r < ra.used; r++) {
    printf("%s\n", ra.items[r].item);
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
