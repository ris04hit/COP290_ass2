#ifndef LIST_H
#define LIST_H
struct list {
	struct listentry *head; ///< head of the list
	struct listentry *tail; ///< tail of the list
};

struct listentry {
	void *data;		///< data for this entry
	struct listentry *prev; ///< previous entry
	struct listentry *next; ///< next entry
};

void list_rm(struct list *l, struct listentry *e);		// Remove an item from the list
struct listentry *list_add(struct list *l, void *data); 	// Add an item to the list
struct list *list_new();					// Return an initialized list
int is_empty(struct list *l);					// Check if list is empty or not
#endif
