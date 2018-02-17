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
#include "PIDInterface.h"

void createThreads(pthread_t *);
void joinThreads(pthread_t *);
void *testManager(void *);

int count;
pthread_mutex_t mut;

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
		fprintf(stderr, "Could not allocate pid.\n");
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
