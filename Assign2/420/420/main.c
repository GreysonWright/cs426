//
//  main.c
//  320
//
//  Created by Greyson Wright on 2/13/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include "PIDManager.h"
const int MIN_PID = 300;
const int MAX_PID = 5000;
const int MAX_MAP = 4701;

pthread_mutex_t mut;
PIDManager *pidManager;

int allocate_map(void);
void createThreads(pthread_t *);
void joinThreads(pthread_t *);
void *testManager(void *);
int allocate_pid(void);
int getMap(void);
void release_pid(int);

int count;

int main() {
	pthread_t *tids = malloc((sizeof *tids) * 100);
	int didAllocMap = allocate_map();
	pthread_mutex_init(&mut, 0);
	srand((unsigned) time(0));
	
	if (!didAllocMap) {
		exit(-1);
	}
	
	createThreads(tids);
	joinThreads(tids);
	return 0;
}

int allocate_map() {
	pidManager = newPIDManager(MAX_MAP);
	if (pidManager == 0) {
		printf("Could not allocate map.\n");
		return -1;
	}
	return 1;
}

void createThreads(pthread_t *tids) {
	for (int i = 0; i < 100; i++) {
		pthread_create(&tids[i], 0, testManager, 0);
	}
}

void joinThreads(pthread_t *tids) {
	for (int i = 0; i < 100; i++) {
		pthread_join(tids[i], 0);
	}
}

void *testManager(void *args) {
	(void)args;
	pthread_mutex_lock(&mut);
	int pid = allocate_pid();
	pthread_mutex_unlock(&mut);
	
	if (pid == -1) {
		printf("Could not allocate pid.\n");
		pthread_exit(0);
	}
	
	printf("allocated %d\n",pid);
	
	sleep(rand() % 5);
	
	pthread_mutex_lock(&mut);
	release_pid(pid);
	pthread_mutex_unlock(&mut);
	
	printf("released %d\n",pid);
	
	pthread_exit(0);
}

int allocate_pid() {
	return createProcess(pidManager);
}

void release_pid(int pid) {
	removeProcess(pidManager, pid);
}
