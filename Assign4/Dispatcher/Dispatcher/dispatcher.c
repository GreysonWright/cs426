//
//  main.c
//  Dispatcher
//
//  Created by Greyson Wright on 3/16/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include "scanner.h"
#include "queue.h"
#include "job.h"

int main(int argc, const char **argv) {
	FILE *input = fopen(argv[1], "r");
	int arrivalTime = readInt(input);
	int priority = readInt(input);
	int processorTime = readInt(input);
	while (!feof(input)) {
		arrivalTime = readInt(input);
		priority = readInt(input);
		processorTime = readInt(input);
	}
	fclose(input);
	return 0;
}
