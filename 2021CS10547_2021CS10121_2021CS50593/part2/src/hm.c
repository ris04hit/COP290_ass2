#include "../include/mythread.h"
#include "../include/list.h"
#include <string.h>
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
    h->lk[i] = NULL;
  }
  *out_hashmap = *h;
  return 0;
}

int hash_func(const char* key){
  int p = 257;
  int m = 4093;
  char k = key[0];
  int i = 0;
  int hash_code = 0;
  while (i < strlen(key)){
    // printf("%d\n", k);
    // puts(k);
    // printf("comp\n");
    int asc = (int) k;
    if (asc < 0){asc = -asc;}
    hash_code = (p*hash_code + asc)%m;
    i++;
    k = key[i];
  }
  return hash_code;
}

int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data)   // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function
{
  // printf("Call by put %s\n", key);
  int hash_code = hash_func(key);
  struct hashmap_element_s* elem = (struct hashmap_element_s*)malloc(sizeof(struct hashmap_element_s));
  char* k = (char*)malloc((strlen(key)+1)*sizeof(char));
  for (int i = 0; i<=strlen(key); i++){
    *(k+i) = *(key+i);
  }
  elem->key = k;
  elem->data = data;
  if (hashmap->table[hash_code] == NULL){
    hashmap->table[hash_code] = list_new(); 
    struct listentry* n = list_add(hashmap->table[hash_code], (void*) elem);
  }
  else{
    struct listentry* Node = hashmap->table[hash_code]->head;
    while (Node != NULL){
      if (strcmp(((struct hashmap_element_s *)(Node->data))->key,key)==0){
        free(((struct hashmap_element_s *)(Node->data))->key);
        free(Node->data);
        list_rm(hashmap->table[hash_code], Node);
        break;
      }
      else{
        Node = Node->next;
      }
    }
    struct listentry* n = list_add(hashmap->table[hash_code], (void*) elem);
  }
}

void* hashmap_get(struct hashmap_s *const hashmap, const char* key)    // Fetch value of a key from hashmap
{
  printf("Call by get %s\n", key);
  int hash_code = hash_func(key);
  // printf("%d\n",hash_code);
  if (hashmap->table[hash_code] == NULL){return NULL;}
  // printf("b\n");
  struct listentry* Node = hashmap->table[hash_code]->head;
  while (Node != NULL){
    if (strcmp(((struct hashmap_element_s *)(Node->data))->key,key)==0){
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

int acquire_bucket(struct hashmap_s *const hashmap, const char* key)   // Acquire lock on a hashmap slot
{
    // printf("Call by ab\n");// %s\n", key);
    // puts(key);
    // printf("done %ld\n", strlen(key));
  int hash_code = hash_func(key);
  // printf("acq buck hash code %d\n",hash_code);
  if (hashmap->lk[hash_code] == NULL){
    hashmap->lk[hash_code] = lock_new();
    // printf("New lock\n");
  }
  lock_acquire(hashmap->lk[hash_code]);
  // printf("Lock acquired\n");
}

int release_bucket(struct hashmap_s *const hashmap, const char* key)   // Release acquired lock
{
    // printf("Call by rb %s\n", key);
  int  hash_code = hash_func(key);
  if (hashmap->lk[hash_code] != NULL){
    lock_release(hashmap->lk[hash_code]);
  }
}
