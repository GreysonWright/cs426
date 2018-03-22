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

int max(int a, int b);
int min(int a, int b);

Job *newJob(int arrivalTime, int priority, int processorTime) {
	Job *job = malloc(sizeof *job);
	job->arrivalTime = arrivalTime;
	job->priority = priority;
	job->processorTime = processorTime;
	return job;
}

int isSystemJob(Job *job) {
	return getPriorityJob(job) == 0;
}

int isSuspendedJob(Job *job) {
	return getPIDJob(job) != 0;
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

void incrementArrivalTimeJob(Job *job) {
	job->arrivalTime += 1;
}

int getPriorityJob(Job *job) {
	return job->priority;
}

void lowerPriorityJob(Job *job) {
	job->priority = min(3, job->priority + 1);
}

int min(int a, int b) {
	return a < b ? a : b;
}

int getProcessorTimeJob(Job *job) {
	return job->processorTime;
}

void setProcessorTimeJob(Job *job, int time) {
	job->processorTime = time;
}

void decrementProcessorTimeJob(Job *job) {
	job->processorTime = max(0, job->processorTime - 1);
}

int max(int a, int b) {
	return a > b ? a : b;
}

int compareArrivalJob(void *left, void *right) {
	return getArrivalTimeJob(left) - getArrivalTimeJob(right);
}

int comparePriorityJob(void *left, void *right) {
	return getPriorityJob(left) - getPriorityJob(right);
}

void displayJob(FILE *file, void *job) {
	long pid = (long)getPIDJob(job);
	int arrivalTime = getArrivalTimeJob(job);
	int priority = getPriorityJob(job);
	int processorTime = getProcessorTimeJob(job);
	fprintf(file, "{pid: %ld, arrivalTime: %d, priority: %d, processorTime: %d}", pid, arrivalTime, priority, processorTime);
}
