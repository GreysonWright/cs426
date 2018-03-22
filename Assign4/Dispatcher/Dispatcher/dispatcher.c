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

int doJobsExist(queue *);
void startProcess(Job *);
void restartProcess(Job *);
void suspendProcess(Job *);
void terminateProcesss(Job *);

int currentTime;

int main(int argc, const char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Please include input file.\n");
		return -1;
	}
	
	queue *waitingQueue = newQueue(displayJob, compareArrivalJob);
	queue *jobQeue = newQueue(displayJob, comparePriorityJob);
	currentTime = 0;

	FILE *input = fopen(argv[1], "r");
	while (!feof(input)) {
		int arrivalTime = readInt(input);
		readChar(input);
		int priority = readInt(input);
		readChar(input);
		int processorTime = readInt(input);
		Job *job = newJob(arrivalTime, priority, processorTime);
		enqueue(waitingQueue, job);
	}
	fclose(input);
	
	Job *currentJob = 0;
	while (doJobsExist(jobQeue) || doJobsExist(waitingQueue)) {
		while (sizeQueue(waitingQueue) && getArrivalTimeJob(peekQueue(waitingQueue)) <= currentTime) {
			Job *arrivingJob = dequeue(waitingQueue);
			enqueueMin(jobQeue, arrivingJob);
		}
		
		if (currentJob) {
			decrementProcessorTimeJob(currentJob);
			if (getProcessorTimeJob(currentJob) == 0) {
				terminateProcesss(currentJob);
			} else if (!isSystemJob(currentJob) && getProcessorTimeJob(currentJob) > 0) {
				lowerPriorityJob(currentJob);
				suspendProcess(currentJob);
				enqueueMin(jobQeue, currentJob);
			}
			currentJob = 0;
		}
		
		if (currentJob == 0 && sizeQueue(jobQeue)) {
			currentJob = dequeue(jobQeue);
			if (isSuspendedJob(currentJob)) {
				restartProcess(currentJob);
			} else {
				fflush(stdout);
				startProcess(currentJob);
			}
		}
		sleep(1);
		currentTime += 1;
	}

	return 0;
}

int doJobsExist(queue *queue) {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += sizeQueue(queue);
	}
	return sum;
}

void startProcess(Job *job) {
	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork Failed\n");
	} else if (pid == 0) {
		char *args[2] = {"./process", "20"};
		execvp(args[0], args);
	} else {
		setPIDJob(job, pid);
	}
}

void restartProcess(Job *job) {
	fflush(stdout);
	kill(getPIDJob(job), SIGCONT);
}

void suspendProcess(Job *job) {
	kill(getPIDJob(job), SIGSTOP);
	int status = 0;
	fflush(stdout);
	waitpid(getPIDJob(job), &status, WUNTRACED);
}

void terminateProcesss(Job *job) {
	kill(getPIDJob(job), SIGINT);
	fflush(stdout);
	int status = 0;
	waitpid(getPIDJob(job), &status, WUNTRACED);
}
