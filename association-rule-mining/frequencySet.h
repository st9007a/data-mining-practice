#ifndef FREQUENCY_SET
#define FREQUENCY_SET

struct frequencySet {
  char** prefix;
  char** suffix;
  int count;
  size_t prefixLen;
  size_t prefixSize;
  size_t suffixLen;
  size_t suffixSize;
} fSetDault = { NULL, NULL, 0, 0, 0, 0, 0};

void pushToPrefix(struct frequencySet*, char*);
void pushToSuffix(struct frequencySet*, char*);

#endif
