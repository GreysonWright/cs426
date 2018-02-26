//
//  main.c
//  p536
//
//  Created by Greyson Wright on 2/20/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#define MIN_PID 300
#define MAX_PID 5000
#define MAX_MAP 4701

typedef struct PIDManager {
	int capacity;
	int *map;
} PIDManager;

int incrementPIDCounter(PIDManager *);

PIDManager *newPIDManager(int capacity) {
	PIDManager *manager = malloc(sizeof *manager);
	manager->capacity = capacity;
	manager->map = calloc(capacity, sizeof(int) * capacity);
	return manager;
}

int createProcess(PIDManager *manager) {
	int pid = 0;
	for (pid = 0; pid < manager->capacity; pid++) {
		if (manager->map[pid] == 0) {
			manager->map[pid] = 1;
			return pid + 300;
		}
	}
	return -1;
}

int removeProcess(PIDManager *manager, int pid) {
	int index = pid - 300;
	if (manager->map[index] == 0) {
		return -1;
	}
	manager->map[index] = 0;
	return pid;
}


PIDManager *pidManager;

int allocate_map() {
	pidManager = newPIDManager(MAX_MAP);
	if (pidManager == 0) {
		fprintf(stderr, "Could not allocate map.\n");
		return -1;
	}
	return 1;
}

int allocate_pid() {
	return createProcess(pidManager);
}

void release_pid(int pid) {
	removeProcess(pidManager, pid);
}

void createThreads(pthread_t *);
void joinThreads(pthread_t *);
void *testManager(void *);

pthread_mutex_t mut;
int count;

int main() {
	pthread_t *tids = malloc((sizeof *tids) * 100);
	int didAllocMap = allocate_map();
	pthread_mutex_init(&mut, 0);
	srand((unsigned) time(0));
	
	if (!didAllocMap) {
		fprintf(stderr, "Could not allocate map.\n");
		exit(-1);
	}
	
	count = 0;
	createThreads(tids);
	joinThreads(tids);
	return 0;
}

void createThreads(pthread_t *tids) {
	int i = 0;
	for (i = 0; i < 100; i++) {
		pthread_create(&tids[i], 0, testManager, 0);
	}
}

void joinThreads(pthread_t *tids) {
	int i = 0;
	for (i = 0; i < 100; i++) {
		pthread_join(tids[i], 0);
	}
}

void *testManager(void *args) {
	pthread_mutex_lock(&mut);
	int pid = allocate_pid();
	count += 1;
	pthread_mutex_unlock(&mut);
	
	if (pid == -1) {
		fprintf(stderr, "Could not allocate pid.\n");
		pthread_exit(0);
	}
	
	unsigned long tid = (unsigned long)pthread_self();
	
	int sleepTime = rand() % 5;
	printf("Sleeping Time .%d secs; PID = %d Thread id = %lu; Counter Value = %d\n", sleepTime, pid, tid, count);
	
	sleep(sleepTime);
	
	pthread_mutex_lock(&mut);
	release_pid(pid);
	count -= 1;
	pthread_mutex_unlock(&mut);
	printf("Sleeping Time .%d secs; PID = %d Thread id = %lu; Counter Value = %d\n", sleepTime, pid, tid, count);
	
	pthread_exit(0);
}
