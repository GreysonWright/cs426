//
//  dll.h
//  Assign_0
//
//  Created by Greyson Wright on 1/13/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef __DLL_INCLUDED__
#define __DLL_INCLUDED__

#include <stdio.h>

typedef struct dllnode {
	void *value;
	struct dllnode *prev;
	struct dllnode *next;
} dllnode;

typedef struct dll {
	dllnode *head;
	dllnode *tail;
	
	int size;
	void (*display)(FILE *,void *);
} dll;

extern dll *newDLL(void (*d)(FILE *,void *));            //constructor
extern void *getDLL(dll *items, int index);
extern void insertDLL(dll *items,int index,void *value); //stores a generic value
extern void *removeDLL(dll *items,int index);            //returns a generic value
extern void unionDLL(dll *recipient,dll *donor);         //merge two lists into one
extern int sizeDLL(dll *items);
extern void displayDLL(FILE *,dll *items);
#endif
