//
//  main.c
//  421
//
//  Created by Greyson Wright on 2/12/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <pthread.h>
#include <sys/types.h>
#include "darray.h"
#include "integer.h"

DArray *buildNumbersList(int, const char **);
void *avg(void *);
int sum(DArray *);
void *min(void *);
void *max(void *);

int numAvg;
int numMax;
int numMin;

int main(int argc, const char **argv) {
	if (argc <= 1) {
		fprintf(stderr, "Not enough arguments provided.\n");
		exit(-1);
	}
	numAvg = 0;
	numMax = 0;
	numMin = 0;
	DArray *numbers = buildNumbersList(argc, argv);
	
	pthread_t tid_avg;
	pthread_t tid_max;
	pthread_t tid_min;
	pthread_create(&tid_avg, 0, avg, numbers);
	pthread_create(&tid_min, 0, min, numbers);
	pthread_create(&tid_max, 0, max, numbers);
	pthread_join(tid_avg, NULL);
	pthread_join(tid_min, NULL);
	pthread_join(tid_max, NULL);
	
	printf("The average value is: %d\n", numAvg);
	printf("The minimum value is: %d\n", numMin);
	printf("The maximum value is: %d\n", numMax);
	return 0;
}

DArray *buildNumbersList(int argc, const char **argv) {
	DArray *numbers = newDArray(0);
	for (int i = 1; i < argc; i++) {
		int number = atoi(argv[i]);
		insertDArray(numbers, newInteger(number));
	}
	return numbers;
}

void *avg(void *args) {
	int numSum = sum(args);
	numAvg = numSum / sizeDArray(args);
	pthread_exit(0);
}

int sum(DArray *numbers) {
	double sum = 0;
	for (int i = 0; i < sizeDArray(numbers); i++) {
		integer *number = getDArray(numbers, i);
		sum += getInteger(number);
	}
	return sum;
}

void *min(void *args) {
	numMin = getInteger(getDArray(args, 0));
	for (int i = 1; i < sizeDArray(args); i++) {
		integer *number = getDArray(args, i);
		numMin = fmin(numMin, getInteger(number));
	}
	pthread_exit(0);
}

void *max(void *args) {
	numMax = getInteger(getDArray(args, 0));
	for (int i = 1; i < sizeDArray(args); i++) {
		integer *number = getDArray(args, i);
		numMax = fmax(numMax, getInteger(number));
	}
	pthread_exit(0);
}
