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
#include "Double.h"

DArray *buildNumbersList(int, const char **);
void *avg(void *);
double sum(DArray *);
void *max(void *);
void *min(void *);

double numAvg;
int numMax;
int numMin;

int main(int argc, const char **argv) {
	numAvg = 0;
	numMax = 0;
	numMin = 0;
	DArray *numbers = buildNumbersList(argc, argv);
	
	pthread_t tid_avg;
	pthread_t tid_max;
	pthread_t tid_min;
	pthread_create(&tid_avg, 0, avg, numbers);
	pthread_create(&tid_max, 0, max, numbers);
	pthread_create(&tid_min, 0, min, numbers);
	pthread_join(tid_avg, NULL);
	pthread_join(tid_max, NULL);
	pthread_join(tid_min, NULL);
	
	printf("The average value is: %lf\n", numAvg);
	printf("The minimum value is: %d\n", numMax);
	printf("The maximum value is: %d\n", numMax);
	return 0;
}

DArray *buildNumbersList(int argc, const char **argv) {
	DArray *numbers = newDArray(0);
	for (int i = 1; i < argc; i++) {
		int number = atof(argv[i]);
		insertDArray(numbers, newDouble(number));
	}
	return numbers;
}

void *avg(void *args) {
	double numSum = sum(args);
	numAvg = numSum / sizeDArray(args);
	pthread_exit(0);
}

double sum(DArray *numbers) {
	double sum = 0;
	for (int i = 0; i < sizeDArray(numbers); i++) {
		Double *number = getDArray(numbers, i);
		sum += getDouble(number);
	}
	return sum;
}

void *max(void *args) {
	pthread_exit(0);
}

void *min(void *args) {
	pthread_exit(0);
}
