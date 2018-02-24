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
int buf_front;
int buf_back;
pthread_mutex_t mut;
sem_t *full;
sem_t *empty;

int main(int argc, const char **argv) {
	if(argc != 4) {
		fprintf(stderr, "insufficient number of arguments.\n");
		return -1;
	}
	
	int sleepTime = atoi(argv[1]);
	int producerCount = atoi(argv[2]);
	int consumerCount = atoi(argv[3]);
	pthread_t *producerTIDs = createThreads(producer, producerCount);
	pthread_t *consumerTIDs = createThreads(consumer, consumerCount);
	joinThreads(producerTIDs);
	joinThreads(consumerTIDs);
	
	srand((unsigned)time(0));
	pthread_mutex_init(&mut, 0);
	full = sem_open(0, 0);
	empty = sem_open(0, 5);
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
			printf("producer produced %d\n",item);
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
			printf("consumer consumed %d\n",item);
		}
	}
}

int insert_item(buffer_item item) {
	sem_wait(empty);
	pthread_mutex_lock(&mut);
	buffer[buf_front] = item;
	buf_front = (buf_front + 1) % BUFFER_SIZE;
	pthread_mutex_unlock(&mut);
	sem_post(full);
	return 0;
}

int remove_item(buffer_item *item) {
	sem_wait(empty);
	pthread_mutex_lock(&mut);
	*item = buffer[buf_back];
	buffer[buf_back] = -1;
	buf_front = (buf_back - 1) % BUFFER_SIZE;
	pthread_mutex_unlock(&mut);
	sem_post(full);
	return 0;
}
