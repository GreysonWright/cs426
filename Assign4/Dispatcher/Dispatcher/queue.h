//
//  queue.h
//  Assign_0
//
//  Created by Greyson Wright on 1/14/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

typedef struct queue queue;

queue *newQueue(void (*)(FILE *, void *), int (*)(void *, void *));
void enqueue(queue *, void *);
void *dequeue(queue *);
void *peekQueue(queue *);
int sizeQueue(queue *);
void displayQueue(FILE *, queue *);
#endif /* queue_h */
