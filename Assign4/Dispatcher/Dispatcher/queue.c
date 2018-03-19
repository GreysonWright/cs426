//
//  queue.c
//  Assign_0
//
//  Created by Greyson Wright on 1/14/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include "queue.h"

struct queue {
	sll *list;
	int (*compare)(void *, void *);
};

queue *newQueue(void (*d)(FILE *, void *), int (*compare)(void *, void *)) {
	queue *nQueue = malloc(sizeof *nQueue);
	if (nQueue == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	
	nQueue->list = newSLL(d);
	nQueue->compare = compare;
	return nQueue;
}

void enqueue(queue *items, void *value) {
	for (int i = 0; i < sizeSLL(items->list); i++) {
		void *currentItem = getSLL(items->list, i);
		if (items->compare(currentItem, value) >= 0) {
			insertSLL(items->list, i, value);
			return;
		}
	}
	insertSLL(items->list, items->list->size, value);
}

void *dequeue(queue *items) {
	return removeSLL(items->list, 0);
}

void *peekQueue(queue *items) {
	return getSLL(items->list, 0);
}

int sizeQueue(queue *items) {
	return items->list->size;
}

void displayQueue(FILE *fp, queue *items) {
	displaySLL(fp, items->list);
}
