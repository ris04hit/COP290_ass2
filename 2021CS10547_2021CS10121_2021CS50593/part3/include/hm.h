#include "mythread.h"
#include "list.h"
#define SZ 4096

struct hashmap_element_s {
  char *key;
  void *data;
};

struct hashmap_s {
  struct list* table[SZ];
  struct lock* lk[SZ];
};


int hashmap_create(struct hashmap_s *const out_hashmap);
int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data);
void* hashmap_get(struct hashmap_s *const hashmap, const char* key);
void hashmap_iterator(struct hashmap_s* const hashmap, 
                        int (*f)(struct hashmap_element_s *const));

int acquire_bucket(struct hashmap_s *const hashmap, const char* key);
int release_bucket(struct hashmap_s *const hashmap, const char* key);