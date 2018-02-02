//
//  stack.h
//  Assign_0
//
//  Created by Greyson Wright on 1/13/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>
#include "dll.h"

typedef struct stack {
	dll *list;
} stack;

stack *newStack(void (*d)(FILE *,void *));   //constructor
void push(stack *items, void *value);        //stores a generic value
void *pop(stack *items);                     //returns a generic value
void *peekStack(stack *items);               //returns a generic value
int sizeStack(stack *items);
void displayStack(FILE *,stack *items);
#endif /* stack_h */
