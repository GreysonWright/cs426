//
//  PIDManager.c
//  320
//
//  Created by Greyson Wright on 2/13/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include "PIDManager.h"

struct PIDManager {
	int count;
	int capacity;
	int *map;
};

PIDManager *newPIDManager(int capacity) {
	PIDManager *manager = malloc(sizeof *manager);
	manager->capacity = capacity;
	manager->count = 0;
	manager->map = calloc(capacity, capacity);
	return manager;
}

int createProcess(PIDManager *manager) {
//	int nextPID = (manager->count + 1)
//	if (countPIDManager(manager) < manager->capacity) {
//		manager->map[] = 1;
//		return countPIDManager(manager);
//	}
	return -1;
}

int countPIDManager(PIDManager *manager) {
	return manager->count;
}
