#ifndef CANDIDATE
#define CANDIDATE

struct candidate{
  char** c_list;
  int count;
  int level;
};

struct candidate_table {
  struct candidate* candidate;
  unsigned int length;
  unsigned int size;
};

void init_candidate_table(struct candidate_table*, unsigned int);
void add_new_candidate(struct candidate_table*, struct candidate);
struct string_array generate_l(struct candidate_table*);

#endif
