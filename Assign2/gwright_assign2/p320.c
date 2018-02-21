//
//  PIDInterface.c
//
//  Created by Greyson Wright on 2/16/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include "p320.h"

PIDManager *pidManager;

int allocate_map() {
	pidManager = newPIDManager(MAX_MAP);
	if (pidManager == 0) {
		fprintf(stderr, "Could not allocate map.\n");
		return -1;
	}
	return 1;
}

int allocate_pid() {
	return createProcess(pidManager);
}

void release_pid(int pid) {
	removeProcess(pidManager, pid);
}
