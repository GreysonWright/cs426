//
//  PIDManager.c
//  320
//
//  Created by Greyson Wright on 2/13/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include "PIDManager.h"

struct PIDManager {
	int capacity;
	int *map;
};

int incrementPIDCounter(PIDManager *);

PIDManager *newPIDManager(int capacity) {
	PIDManager *manager = malloc(sizeof *manager);
	manager->capacity = capacity;
	manager->map = calloc(capacity, capacity);
	return manager;
}

int createProcess(PIDManager *manager) {
	for (int pid = 0; pid < manager->capacity; pid++) {
		if (manager->map[pid] == 0) {
			manager->map[pid] = 1;
			return pid + 300;
		}
	}
	return -1;
}

int removeProcess(PIDManager *manager, int pid) {
	int index = pid - 300;
	if (manager->map[index] == 0) {
		return -1;
	}
	manager->map[index] = 0;
	return pid;
}

