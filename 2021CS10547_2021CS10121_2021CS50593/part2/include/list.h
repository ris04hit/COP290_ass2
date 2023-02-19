#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdlib.h>

struct list {
	struct listentry* head;
	struct listentry* tail;
};

struct listentry {
	void *data;
	struct listentry *prev;
	struct listentry *next;
};

void list_rm(struct list* l, struct listentry* e)    // Remove an item from the list
{
	if (l->head == e){
		if (e->next == NULL){
			l->head = NULL;
			l->tail = NULL;
		}
		else{
			e->next->prev = NULL;
			l->head = e->next;
		}
	}
	else{
		if (e->next == NULL){
			l->tail = e->prev;
			l->tail->next = NULL;
		}
		else{
			e->prev->next = e->next;
			e->next->prev = e->prev;
		}
	}
	free(e);
}

int is_empty(struct list* l)  // Check if list is empty or not
{
	if ((l->head == NULL) && (l -> tail == NULL)) {
		return 1;
	} 
	else {
		return 0;
	}
}

struct listentry* list_add(struct list* l, void* data)  // Add an item to the list
{
	struct listentry* Node = (struct listentry*)malloc(sizeof(struct listentry));
	Node->data = data;
	if (is_empty(l) == 0){
		Node->prev = l->tail;
		l->tail->next = Node;
		l->tail = Node;
	}
	else{
		l->head = Node;
		l->tail = Node;
	}
	return Node;
}

struct list* list_new()  // Return an initialized list
{
	struct list* l;
	l = (struct list*)malloc(sizeof(struct list));
	return l;
}

#endif