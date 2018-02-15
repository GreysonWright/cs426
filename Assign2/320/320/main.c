//
//  main.c
//  320
//
//  Created by Greyson Wright on 2/13/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "PIDManager.h"
const int MIN_PID = 300;
const int MAX_PID = 5000;
const int MAX_MAP = 4701;

PIDManager *pidManager;

int allocate_map(void);
int allocate_pid(void);
int getMap(void);
void release_pid(int);

int count;

int main() {
	allocate_map();
	for (int i = 0; i < MAX_MAP; i++) {
		int pid = allocate_pid();
		printf("%d\n", pid);
	}
	for (int i = 0; i < MAX_MAP; i++) {
		release_pid(i);
	}
	return 0;
}

int allocate_map() {
	pidManager = newPIDManager(MAX_MAP);
	
	return 1;
}

int allocate_pid() {
	return createProcess(pidManager);
}

void release_pid(int pid) {
	removeProcess(pidManager, pid);
}
