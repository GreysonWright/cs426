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
void restartProcess(Job *);
void suspendProcess(Job *);
void terminateProcesss(Job *);

queue *queues[4];

int main(int argc, const char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Please include input file.\n");
		return -1;
	}
	
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
	
	while (sizeQueue(queues[0]) + sizeQueue(queues[1]) + sizeQueue(queues[2]) + sizeQueue(queues[3]) > 0) {
		int minPriority = 0;
		Job *currentJob = 0;
		for (int i = 0; i < 4; i++) {
			Job *peekJob = peekQueue(queues[i]);
			Job *minJob = peekQueue(queues[minPriority]);
			if (peekJob && minJob && getArrivalTimeJob(peekJob) < getArrivalTimeJob(minJob)) {
				minPriority = i;
			}
		}
		
		currentJob = dequeue(queues[minPriority]);
		if (isSuspendedJob(currentJob)) {
			restartProcess(currentJob);
		} else {
			startProcess(currentJob);
		}
		
		if (!isSystemJob(currentJob)) {
			lowerPriorityJob(currentJob);
			decrementProcessorTimeJob(currentJob);
			sleep(1);
		}
		
		if (getProcessorTimeJob(currentJob) > 0) {
			suspendProcess(currentJob);
			enqueue(queues[getPriorityJob(currentJob)], currentJob);
		} else {
			terminateProcesss(currentJob);
		}
		int status = 0;
		waitpid(getPIDJob(currentJob), &status, WUNTRACED);
	}
	
	return 0;
}

void startProcess(Job *job) {
	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork Failed\n");
	} else if (pid == 0) {
		char *args[2] = {"./process", "5"};
		execvp(args[0], args);
	} else {
		setPIDJob(job, pid);
	}
}

void restartProcess(Job *job) {
	kill(getPIDJob(job), SIGCONT);
}

void suspendProcess(Job *job) {
	kill(getPIDJob(job), SIGINT);
}

void terminateProcesss(Job *job) {
	kill(getPIDJob(job), SIGSTOP);
}
