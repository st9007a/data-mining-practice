#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  float minSup;
  float minConf;
  FILE* record;
  char* line;
  size_t len = 0;
  ssize_t read;

  printf("Input your minimum support : ");
  scanf("%f", &minSup);

  printf("\nInput your minimum confidence : ");
  scanf("%f", &minConf);

  record = fopen("input.txt", "r");

  if (record == NULL) {
    printf("Read File Error : Can't find a file named input.txt\n");
    exit(1);
  }

  while ((read = getline(&line, &len, record)) != -1) {
    //parse to array
    
  }
}
