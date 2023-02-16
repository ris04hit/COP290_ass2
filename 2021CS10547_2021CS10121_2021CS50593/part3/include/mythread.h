#ifndef THREAD_H
#define THREAD_H

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>

void mythread_init();
void* mythread_create(void func(void*), void* arg);
void mythread_join();
void mythread_yield();

struct lock {
	void* c;
};
struct lock* lock_new();
void lock_acquire(struct lock* lk);
int lock_release(struct lock* lk);

#endif
