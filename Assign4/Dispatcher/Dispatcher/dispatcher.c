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
Job *startProcess(Job *);
Job *restartProcess(Job *);
Job *suspendProcess(Job *);
Job *terminateProcesss(Job *);

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
		enqueueMin(waitingQueue, job);
	}
	fclose(input);
	
	Job *currentJob = 0;
	while (currentJob || doJobsExist(jobQeue) || doJobsExist(waitingQueue)) {
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
		} else if (currentJob == 0 && sizeQueue(jobQeue)) {
			currentJob = dequeue(jobQeue);
			if (isSuspendedJob(currentJob)) {
				restartProcess(currentJob);
			} else {
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

Job *startProcess(Job *job) {
	setPIDJob(job, fork());
	if (getPIDJob(job) < 0) {
		fprintf(stderr, "Fork Failed\n");
		return 0;
	} else if (getPIDJob(job) == 0) {
		char *args[2] = {"./process", 0};
		execvp(args[0], args);
		return job;
	} else {
		return job;
	}
}

Job *restartProcess(Job *job) {
	if (kill(getPIDJob(job), SIGCONT)) {
		printf("Could not restart process %ld.\n", (long)getPIDJob(job));
		return 0;
	}
	return job;
}

Job *suspendProcess(Job *job) {
	if (kill(getPIDJob(job), SIGTSTP)) {
		printf("Could not suspend process %ld.\n", (long)getPIDJob(job));
		return 0;
	}
	int status;
	waitpid(getPIDJob(job), &status, WUNTRACED);
	return job;
}

Job *terminateProcesss(Job *job) {
	if (kill(getPIDJob(job), SIGINT)) {
		printf("Could not terminate process %ld.\n", (long)getPIDJob(job));
		return 0;
	}
	int status;
	waitpid(getPIDJob(job), &status, WUNTRACED);
	return job;
}
