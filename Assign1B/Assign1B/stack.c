//
//  stack.c
//  Assign_0
//
//  Created by Greyson Wright on 1/13/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include "stack.h"
#include <stdlib.h>

stack *newStack(void (*d)(FILE *,void *)) {
	stack *nStack = malloc(sizeof *newStack);
	if (nStack == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	
	nStack->list = newDLL(d);
	return nStack;
}

void push(stack *items, void *value) {
	insertDLL(items->list, 0, value);
}

void *pop(stack *items) {
	return removeDLL(items->list, 0);
}

void *peekStack(stack *items) {
	return getDLL(items->list, 0);
}

int sizeStack(stack *items) {
	return items->list->size;
}

void displayStack(FILE *file ,stack *items) {
	displayDLL(file, items->list);
}
