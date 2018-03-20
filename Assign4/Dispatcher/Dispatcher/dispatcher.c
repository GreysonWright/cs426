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

void execArgs(char **);

int main(int argc, const char **argv) {
	queue *queues[4] = {newQueue(displayJob, compareJob), newQueue(displayJob, compareJob), newQueue(displayJob, compareJob), newQueue(displayJob, compareJob)};
	FILE *input = fopen(argv[1], "r");
	while (!feof(input)) {
		int arrivalTime = readInt(input);
		readChar(input);
		int priority = readInt(input);
		readChar(input);
		int processorTime = readInt(input);
		Job *job = newJob(arrivalTime, priority, processorTime);
		enqueue(queues[priority], job);
	}
	fclose(input);
	
	while (sizeQueue(queues[0]) + sizeQueue(queues[1]) + sizeQueue(queues[2]) + sizeQueue(queues[3]) > 0) {
		int minPriority = 0;
		for (int i = 0; i < 4; i++) {
			Job *peekJob = peekQueue(queues[i]);
			Job *minJob = peekQueue(queues[minPriority]);
			if (getArrivalTimeJob(peekJob) < getArrivalTimeJob(minJob)) {
				minPriority = i;
			}
		}
		char *args[2] = {"./process", ""};
		execArgs(args);
	}
	
	return 0;
}

void execArgs(char **args) {
	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork Failed\n");
	} else if (pid == 0) {
		execvp(args[0], args);
	} else if (pid > 0) {
		while (pid != wait(0));
	}
}
