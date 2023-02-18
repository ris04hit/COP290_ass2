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


int hashmap_create(struct hashmap_s *const out_hashmap)   // Initialize a hashmap
{
  struct hashmap_s* h = (struct hashmap_s*)malloc(sizeof(struct hashmap_s));
  for(int i=0; i<SZ; i++){
    h->table[i] = NULL;
  }
  *out_hashmap = *h;
  return 0;
}

int hash_func(const char* key){
  int p = 257;
  int m = 4093;
  char *k = (char*) key;
  int hash_code = 0;
  while (*k != '\0'){
    int asc = (int) *k;
    hash_code = (p*hash_code + asc)%m;
    k++;
  }
}

int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data)   // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function
{
  int hash_code = hash_func(key);
  struct hashmap_element_s* elem = (struct hashmap_element_s*)malloc(sizeof(struct hashmap_element_s));
  elem->key = (char*) key;
  elem->data = data;
  if (hashmap->table[hash_code] == NULL){
    hashmap->table[hash_code] = list_new(); 
    struct listentry* n = list_add(hashmap->table[hash_code], (void*) elem);
  }
  else{
    struct listentry* Node = hashmap->table[hash_code]->head;
    while (Node != NULL){
      if (((struct hashmap_element_s *)(Node->data))->key == key){
        Node->data = (void*) elem;
        break;
      }
      else{
        Node = Node->next;
      }
      if (Node == NULL){
        struct listentry* n = list_add(hashmap->table[hash_code], (void*) elem);
      }
    }
  }
}

void* hashmap_get(struct hashmap_s *const hashmap, const char* key)    // Fetch value of a key from hashmap
{
  int hash_code = hash_func(key);
  struct listentry* Node = hashmap->table[hash_code]->head;
  while (Node != NULL){
    if (((struct hashmap_element_s *)(Node->data))->key == key){
      return ((struct hashmap_element_s *)(Node->data))->data;
    }
    else{
      Node = Node->next;
    }
  }
  return NULL;
}

void hashmap_iterator(struct hashmap_s* const hashmap, int (*f)(struct hashmap_element_s *const))  // Execute argument function on each key-value pair in hashmap
{
  for (int i = 0; i<SZ; i++){
    if (hashmap->table[i] != NULL){
      struct listentry* Node = hashmap->table[i]->head;
      while (Node != NULL){
        int n = f((struct hashmap_element_s *)(Node->data));
        Node = Node->next;
      }
    }
  }
}

int acquire_bucket(struct hashmap_s *const hashmap, const char* key);   // Acquire lock on a hashmap slot
int release_bucket(struct hashmap_s *const hashmap, const char* key);   // Release acquired lock
