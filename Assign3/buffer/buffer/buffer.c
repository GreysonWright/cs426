//
//  buffer.c
//  buffer
//
//  Created by Greyson Wright on 2/23/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include "buffer.h"

pthread_t *createThreads(void *(*)(void *), int );
void joinThreads(pthread_t *);
void *producer(void *param);
void *consumer(void *param);

buffer_item buffer[BUFFER_SIZE];
int in;
int out;
sem_t mut;
sem_t full;
sem_t empty;

int main(int argc, const char **argv) {
	if(argc != 4) {
		fprintf(stderr, "insufficient number of arguments.\n");
		return -1;
	}
	
	int sleepTime = atoi(argv[1]);
	int producerCount = atoi(argv[2]);
	int consumerCount = atoi(argv[3]);
	for (int i = 0; i < BUFFER_SIZE; i++) {
		buffer[i] = -1;
	}
	in = 0;
	out = 0;
	mut = 1;
	full = 0;
	empty = BUFFER_SIZE;
	sem_init(&mut, 0, 1);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFFER_SIZE);
	srand((unsigned)time(0));
	pthread_t *producerTIDs = createThreads(producer, producerCount);
	pthread_t *consumerTIDs = createThreads(consumer, consumerCount);
	joinThreads(producerTIDs);
	joinThreads(consumerTIDs);
	
	sleep(sleepTime);
	return 0;
}

pthread_t *createThreads(void *(*runner)(void *), int count) {
	pthread_t *tids = malloc(count * sizeof *tids);
	for (int i = 0; i < count; i++) {
		pthread_create(&tids[i], 0, runner, 0);
	}
	return tids;
}

void joinThreads(pthread_t *tids) {
	for (int i = 0; i < 100; i++) {
		pthread_join(tids[i], 0);
	}
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
			printf("producer produced %d\n", item);
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
			printf("consumer consumed %d\n", item);
		}
	}
}

int insert_item(buffer_item item) {
	sem_wait(&empty);
	sem_wait(&mut);
	int error = buffer[in] != -1;
	buffer[in] = item;
	in = (in + 1) % BUFFER_SIZE;
	sem_post(&mut);
	sem_post(&full);
	if (error) {
		return -1;
	}
	return 0;
}

int remove_item(buffer_item *item) {
	sem_wait(&full);
	sem_wait(&mut);
	*item = buffer[out];
	buffer[out] = -1;
	out = (out + 1) % BUFFER_SIZE;
	sem_post(&mut);
	sem_post(&empty);
	if (*item == -1) {
		return -1;
	}
	return 0;
}
