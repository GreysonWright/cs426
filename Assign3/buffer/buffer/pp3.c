//
//  buffer.c
//  buffer
//
//  Created by Greyson Wright on 2/23/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>

#define BUFFER_SIZE 5

typedef int buffer_item;

int *getArgs(const char **);
int checkArgs(int *);
void initBuffer(void);
void initSemaphores(void);
pthread_t *createThreads(void *(*)(void *), int );
void *producer(void *param);
void *consumer(void *param);
int insert_item(buffer_item);
int remove_item(buffer_item *);

buffer_item buffer[BUFFER_SIZE];
int bufCount;
int in;
int out;
sem_t mut;
sem_t full;
sem_t empty;

int main(int argc, const char **argv) {
	if(argc != 4) {
		fprintf(stderr, "Insufficient number of arguments.\n");
		return -1;
	}
	
	int *args = getArgs(argv);
	if (!checkArgs(args)) {
		fprintf(stderr, "Negative integers not allowed.\n");
		return -1;
	}
	
	initBuffer();
	initSemaphores();
	srand((unsigned)time(0));

	(void)createThreads(producer, args[1]);
	(void)createThreads(consumer, args[2]);

	sleep(args[0]);
	return 0;
}

int *getArgs(const char **argv) {
	int *args = malloc(3 * sizeof *args);
	int i = 0;
	for (i = 0; i < 3; i++) {
		args[i] = atoi(argv[i + 1]);
	}
	return args;
}

int checkArgs(int *args) {
	int i = 0;
	for (i = 0; i < 3; i++) {
		if (args[i] < 0) {
			return 0;
		}
	}
	return 1;
}

void initBuffer(void) {
	int i = 0;
	for (i = 0; i < BUFFER_SIZE; i++) {
		buffer[i] = -1;
	}
	bufCount = 0;
	in = 0;
	out = 0;
}

void initSemaphores(void) {
	sem_init(&mut, 0, 1);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFFER_SIZE);
}

pthread_t *createThreads(void *(*runner)(void *), int count) {
	pthread_t *tids = malloc(count * sizeof *tids);
	int i = 0;
	for (i = 0; i < count; i++) {
		pthread_create(&tids[i], 0, runner, 0);
	}
	return tids;
}

void *producer(void *param) {
	buffer_item item;
	while (1) {
		int time = rand() % 5;
		sleep(time);
		item = rand();
		if (insert_item(item) == -1) {
			fprintf(stderr, "Error inserting item.\n");
		} else {
			unsigned long tid = (unsigned long)pthread_self();
			printf("%lu produced %d\n", tid, item);
		}
	}
}
		
void *consumer(void *param) {
	buffer_item item;
	while (1) {
		int time = rand() % 5;
		sleep(time);
		if (remove_item(&item) == -1) {
			fprintf(stderr, "Error removing item.\n");
		} else {
			unsigned long tid = (unsigned long)pthread_self();
			printf("%lu consumed %d\n", tid, item);
		}
	}
}

int insert_item(buffer_item item) {
	unsigned long tid = (unsigned long)pthread_self();
	printf("%lu waiting to insert\n", tid);
	sem_wait(&empty);
	sem_wait(&mut);
	printf("%lu signaled to insert\n", tid);
	if (buffer[in] != -1) {
		sem_post(&mut);
		sem_post(&full);
		return -1;
	}
	buffer[in] = item;
	in = (in + 1) % BUFFER_SIZE;
	bufCount++;
	printf("Buffer size: %d\n", bufCount);
	sem_post(&mut);
	sem_post(&full);
	return 0;
}

int remove_item(buffer_item *item) {
	unsigned long tid = (unsigned long)pthread_self();
	printf("%lu waiting to remove\n", tid);
	sem_wait(&full);
	sem_wait(&mut);
	printf("%lu signaled to remove\n", tid);
	*item = buffer[out];
	if (*item == -1) {
		sem_post(&mut);
		sem_post(&empty);
		return -1;
	}
	buffer[out] = -1;
	out = (out + 1) % BUFFER_SIZE;
	bufCount--;
	printf("Buffer size: %d\n", bufCount);
	sem_post(&mut);
	sem_post(&empty);
	return 0;
}
