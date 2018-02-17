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
#include "PIDInterface.h"

int allocate_map(void);
int allocate_pid(void);
void release_pid(int);

int count;

int main() {
	allocate_map();
	for (int i = 0; i < MAX_MAP; i++) {
		int pid = allocate_pid();
		printf("%d\n", pid);
	}
	for (int i = 300; i < MAX_MAP + 300; i++) {
		release_pid(i);
	}
	return 0;
}
