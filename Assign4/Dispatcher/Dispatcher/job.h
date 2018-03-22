//
//  job.h
//  Dispatcher
//
//  Created by Greyson Wright on 3/18/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#ifndef job_h
#define job_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct Job Job;

Job *newJob(int, int, int);
int getPIDJob(Job *);
void setPIDJob(Job *, pid_t);
int getArrivalTimeJob(Job *);
int getPriorityJob(Job *);
int getProcessorTimeJob(Job *);
int compareJob(void *, void *);
void displayJob(FILE *, void *);
#endif /* job_h */
