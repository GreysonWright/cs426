//
//  dll.c
//  Assign_0
//
//  Created by Greyson Wright on 1/13/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include "dll.h"
#include <stdlib.h>

dllnode *newDLLNode(void *value) {
	dllnode *node = malloc(sizeof *node);
	if (node == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	
	node->value = value;
	node->prev = 0;
	node->next = 0;
	
	return node;
}

dllnode *findDLLNode(dll *items, int index) {
	dllnode *node = items->head;
	int size = items->size - 1;
	
	if (index < size / 2) {
		for (int i = 0; i < index; i++) {
			if (node->next == 0) {
				return 0;
			}
			node = node->next;
		}
	} else {
		node = items->tail;
		for (int i = size; i > index; i--) {
			if (node->prev == 0) {
				return 0;
			}
			node = node->prev;
		}
	}
	
	return node;
}

dll *newDLL(void (*d) (FILE *, void *)) {
	dll *items = malloc(sizeof *items);
	
	if (items == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	
	items->head = 0;
	items->tail = 0;
	items->size = 0;
	items->display = d;
	
	return items;
}

void insertDLL(dll *items, int index, void *value) {
	dllnode *node = items->head;
	dllnode *newNode = newDLLNode(value);
	
	if (index == 0) {
		newNode->next = items->head;
		items->head = newNode;
		if (newNode->next == 0) {
			items->tail = newNode;
		} else {
			newNode->next->prev = newNode;
		}
	} else if (index == items->size) {
		newNode->prev = items->tail;
		items->tail->next = newNode;
		items->tail = newNode;
	} else {
		node = findDLLNode(items, index);
		if (node == 0) {
			fprintf(stderr, "Index out of range.");
			exit(-1);
		}
		
		if (node->prev) {
			newNode->prev = node->prev;
			node->prev->next = newNode;
		}
		newNode->next = node;
		node->prev = newNode;
	}
	
	items->size++;
}

void *getDLL(dll *items, int index) {
	dllnode *node = findDLLNode(items, index);
	
	if (node) {
		return node->value;
	}
	return 0;
}

void *removeDLL(dll *items, int index) {
	dllnode *node = items->head;
	dllnode *prevNode = node->prev;
	void *value = 0;
	
	if (node == 0) {
		return 0;
	}
	
	if (index == 0) {
		if (items->head == items->tail) {
			items->tail = 0;
		}
		value = node->value;
		items->head = node->next;
	} else if (index == items->size - 1) {
		node = items->tail;
		prevNode = node->prev;
		value = node->value;
		items->tail = prevNode;
		prevNode->next = 0;
	} else {
		node = findDLLNode(items, index);
		
		value = node->value;
		prevNode = node->prev;
		prevNode->next = node->next;
	}
	
	if (node->next) {
		node->next->prev = prevNode;
	}
	
	items->size--;
	
	return value;
}

void unionDLL(dll *recipient, dll *donor) {
	if (donor == 0 || donor->size == 0) {
		return;
	}
	
	if (recipient->size < 1) {
		recipient->head = donor->head;
		recipient->tail = donor->tail;
		recipient->size = donor->size;
	} else {
		recipient->tail->next = donor->head;
		donor->head->prev = recipient->tail;
		recipient->tail = donor->tail;
		recipient->size += donor->size;
	}
	
	donor->head = 0;
	donor->tail = 0;
	donor->size = 0;
}

int sizeDLL(dll *items) {
	return items->size;
}

void displayDLL(FILE *file, dll *items) {
	dllnode *node = items->head;
	
	fprintf(file, "[");
	while (node) {
		items->display(file, node->value);
		if (node->next) {
			fprintf(file, ",");
		}
		node = node->next;
	}
	fprintf(file, "]");
}
