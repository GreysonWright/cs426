//
//  job.c
//  Dispatcher
//
//  Created by Greyson Wright on 3/18/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include "job.h"

struct Job {
	pid_t pid;
	int arrivalTime;
	int priority;
	int processorTime;
};

Job *newJob(int arrivalTime, int priority, int processorTime) {
	Job *job = malloc(sizeof *job);
	job->arrivalTime = arrivalTime;
	job->priority = priority;
	job->processorTime = processorTime;
	return job;
}

int getPIDJob(Job *job) {
	return job->pid;
}

void setPIDJob(Job *job, pid_t pid) {
	job->pid = pid;
}

int getArrivalTimeJob(Job *job) {
	return job->arrivalTime;
}

int getPriorityJob(Job *job) {
	return job->priority;
}

int getProcessorTimeJob(Job *job) {
	return job->processorTime;
}

int compareJob(void *left, void *right) {
	return getArrivalTimeJob(left) - getArrivalTimeJob(right);
}

void displayJob(FILE *file, void *job) {
	int pid = getPIDJob(job);
	int arrivalTime = getArrivalTimeJob(job);
	int priority = getPriorityJob(job);
	int processorTime = getProcessorTimeJob(job);
	fprintf(file, "{pid: %d, arrivalTime: %d, priority: %d, processorTime: %d}", pid, arrivalTime, priority, processorTime);
}
