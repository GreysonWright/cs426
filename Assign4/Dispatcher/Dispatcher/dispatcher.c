//
//  main.c
//  Dispatcher
//
//  Created by Greyson Wright on 3/16/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "scanner.h"
#include "queue.h"
#include "job.h"

void startProcess(Job *);

queue *queues[4];
int cpuTime;

int main(int argc, const char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Please include input file.\n");
		return -1;
	}
	
	cpuTime = 0;
	queues[0] = newQueue(displayJob, compareJob);
	queues[1] = newQueue(displayJob, compareJob);
	queues[2] = newQueue(displayJob, compareJob);
	queues[3] = newQueue(displayJob, compareJob);

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
	
//	while (sizeQueue(queues[0]) + sizeQueue(queues[1]) + sizeQueue(queues[2]) + sizeQueue(queues[3]) > 0) {
		int minPriority = 0;
		Job *minJob = 0;
		for (int i = 0; i < 4; i++) {
			Job *peekJob = peekQueue(queues[i]);
			minJob = peekQueue(queues[minPriority]);
			if (peekJob && minJob && getArrivalTimeJob(peekJob) < getArrivalTimeJob(minJob)) {
				minPriority = i;
			}
		}
		startProcess(minJob);
//	}
	
	return 0;
}

void startProcess(Job *job) {
	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork Failed\n");
	} else if (pid == 0) {
		setPIDJob(job, getpid());
		printf("%ld\n", (long)getPIDJob(job));
		char *args[2] = {"./process", "5"};
		execvp(args[0], args);
	} else {
		int status = 0;
		printf("test\n");
		waitpid(getPIDJob(job), &status, WUNTRACED);
		printf("done\n");
	}
}
