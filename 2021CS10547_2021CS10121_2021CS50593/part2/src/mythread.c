#ifndef THREAD_H
#define THREAD_H

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>
#include"../include/list.h"

struct list* ctx_list;
struct ucontext_t main_ctx;
struct listentry* curr_elem;

void mythread_init()      // Initialize threads list
{
	ctx_list = list_new();
	getcontext(&main_ctx);
}

ucontext_t* mythread_create(void func(void*), void* arg)  // Create a new thread
{
	ucontext_t *ctx = (ucontext_t *)malloc(sizeof(ucontext_t));
	getcontext(ctx);
	char* stack = (char *)malloc(16384*sizeof(char));
	// printf("%d\n",(int)stack);
	ctx->uc_stack.ss_sp = stack;
	ctx->uc_stack.ss_size = sizeof(stack);
	ctx->uc_link = &main_ctx; 
	void (* funcptr0)(void);
	funcptr0 = (void (*)(void))func;
	makecontext(ctx, funcptr0, 1, arg);
	list_add(ctx_list, (void *)(ctx));
	return ctx;
}

void mythread_join()  // Waits for other thread to complete. It is used in case of dependent threads.
{
	struct listentry* Node = ctx_list->head;
	while (Node != NULL){
		ucontext_t *ctx0 = (ucontext_t *)(Node->data);
		curr_elem = Node;
		swapcontext(&main_ctx, ctx0);
		struct listentry* Node2 = Node->next;
		list_rm(ctx_list, Node);
		Node = Node2;
	}
}

void mythread_yield()  // Perform context switching here
{
	ucontext_t *ctx_curr = (ucontext_t *)(curr_elem->data);
	ucontext_t *ctx_next;
	if (curr_elem != ctx_list->tail){
		ctx_next = (ucontext_t *)(curr_elem->next->data);
		curr_elem = curr_elem->next;
	}
	else{
		ctx_next = (ucontext_t *)(ctx_list->head->data);
		curr_elem = ctx_list->head;
	}
	swapcontext(ctx_curr, ctx_next);
}

struct lock {
	ucontext_t* ctx;
};
struct lock* lock_new();   // return an initialized lock object
void lock_acquire(struct lock* lk);   // Set lock. Yield if lock is acquired by some other thread.
int lock_release(struct lock* lk);   // Release lock

#endif
