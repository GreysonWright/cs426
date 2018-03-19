//
//  sll.h
//  Assign_0
//
//  Created by Greyson Wright on 1/13/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef __SLL_INCLUDED__
#define __SLL_INCLUDED__

#include <stdio.h>

typedef struct sllnode {
	void *value;
	struct sllnode *next;
} sllnode;

typedef struct sll {
	sllnode *head;
	sllnode *tail;
	
	int size;
	void (*display)(FILE *, void *);
} sll;

extern sll *newSLL(void (*d) (FILE *, void *));            //constructor
extern void *getSLL(sll *items, int index);
extern void insertSLL(sll *items, int index, void *value); //stores a generic value
extern void *removeSLL(sll *items, int index);            //returns a generic value
extern void unionSLL(sll *recipient, sll *donor);         //merge two lists into one
extern int sizeSLL(sll *items);
extern void displaySLL(FILE *, sll *items);
#endif
