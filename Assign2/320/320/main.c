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
const int MIN_PID = 300;
const int MAX_PID = 5000;
const int MAX_MAP = 4700;

int *map;

int allocate_map(void);
int allocate_pid(void);
int getMap(void);
void release_pid(int);

int count;

int main(int argc, const char **argv) {
	
	return 0;
}

int allocate_map() {
	map = malloc(MAX_MAP);
	if (map == 0) {
		return -1;
	}
	
	for (int i = 0; i < MAX_MAP; i++) {
		map[i] = -1;
	}
	count = 0;
	
	return 1;
}

int allocate_pid() {
	
	
	int pid = 0;
	
	return 0;
}

void release_pid(int pid) {
	
}
