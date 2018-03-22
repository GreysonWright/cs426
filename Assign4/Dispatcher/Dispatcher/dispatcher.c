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
#include <stdlib.h>
#include "scanner.h"
#include "queue.h"
#include "job.h"

int doJobsExist(void);
Job *findMinJob(void);
void startProcess(Job *);
char *intToString(int);
int countDigits(int);
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
	
	while (doJobsExist()) {
		Job *currentJob = findMinJob();
		
		if (isSuspendedJob(currentJob)) {
			restartProcess(currentJob);
		} else {
			fflush(stdout);
			startProcess(currentJob);
		}
		
		if (!isSystemJob(currentJob)) {
			incrementArrivalTimeJob(currentJob); 
			lowerPriorityJob(currentJob);
			decrementProcessorTimeJob(currentJob);
			sleep(1);
		} else {
			sleep(getProcessorTimeJob(currentJob));
			setProcessorTimeJob(currentJob, 0);
		}
		
		if (getProcessorTimeJob(currentJob) > 0) {
			suspendProcess(currentJob);
			enqueue(queues[getPriorityJob(currentJob)], currentJob);
		} else {
			terminateProcesss(currentJob);
		}
	}
	return 0;
}

int doJobsExist() {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += sizeQueue(queues[i]);
	}
	return sum;
}

Job *findMinJob() {
	int minPriority = 0;
	for (int i = 0; i < 4; i++) {
		Job *peekJob = peekQueue(queues[i]);
		Job *minJob = peekQueue(queues[minPriority]);
		if (peekJob && minJob && getArrivalTimeJob(peekJob) < getArrivalTimeJob(minJob)) {
			minPriority = i;
		}
	}
	return dequeue(queues[minPriority]);
}

void startProcess(Job *job) {
	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork Failed\n");
	} else if (pid == 0) {
		char *processorTimeString = intToString(getProcessorTimeJob(job));
		char *args[2] = {"./process", processorTimeString};
		execvp(args[0], args);
	} else {
		setPIDJob(job, pid);
	}
}

char *intToString(int num) {
	int digitCount = countDigits(num);
	char *numString = malloc(digitCount + 1);
	snprintf(numString, digitCount + 1, "%d", num);
	numString[digitCount] = 0;
	return numString;
}

int countDigits(int a) {
	if (a == 0) {
		return 0;
	}
	return countDigits(a / 10) + 1;
}

void restartProcess(Job *job) {
	kill(getPIDJob(job), SIGCONT);
}

void suspendProcess(Job *job) {
	kill(getPIDJob(job), SIGINT);
	int status = 0;
	waitpid(getPIDJob(job), &status, WUNTRACED);
}

void terminateProcesss(Job *job) {
	kill(getPIDJob(job), SIGSTOP);
	int status = 0;
	waitpid(getPIDJob(job), &status, WUNTRACED);
}
