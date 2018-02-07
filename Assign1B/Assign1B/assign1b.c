//
//  main.c
//  Assign1B
//
//  Created by Greyson Wright on 1/31/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "darray.h"
#define MAX_LINE 80 /* The maximum length command */

char *readLine(FILE *);
void runArgs(char **);
char **buildArgs(char *);
int findAmpersand(char **);
void displayHistory(DArray *);
int min(int, int);
void execHistory(DArray *, int);
int parseInt(char *);

int main(void) {
	char **args = 0;
	int should_run = 1;
	DArray *historyArray = newDArray(0);
	
	while (should_run) {
		printf("osh>");
		fflush(stdout);
		
		char *input = readLine(stdin);
		if (!strcmp(input, "exit\n")) {
			should_run = 0;
		} else if (!strcmp(input, "history\n")) {
			displayHistory(historyArray);
			insertDArray(historyArray, input);
		} else if (!strcmp(input, "!!\n")) {
			if (sizeDArray(historyArray) > 0) {
				execHistory(historyArray, 1);
			} else {
				printf("No commands in history.\n");
			}
		} else if (input[0] == '!') {
			int parsedInt = parseInt(input);
			if (parsedInt > 0 && sizeDArray(historyArray) >= parsedInt) {
				execHistory(historyArray, parsedInt);
			} else {
				printf("No such command in history.\n");
			}
		} else if (!isspace(input[0])) {
			args = buildArgs(input);
			runArgs(args);
			insertDArray(historyArray, input);
		}
	}
	return 0;
}

char *readLine(FILE *file) {
	char *str = malloc(MAX_LINE + 1);
	fgets(str, MAX_LINE, file);
	return str;
}

char **buildArgs(char *str) {
	char **args = malloc(MAX_LINE / 2 + 1);
	char *newString = malloc(MAX_LINE + 1);
	strcpy(newString, str);
	char *token = strtok(newString, " \n");
	int count = 0;
	while (token) {
		args[count++] = token;
		token = strtok(0, " \n");
	}
	args[count] = 0;
	return args;
}

void runArgs(char **args) {
	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork Failed\n");
	} else if (pid == 0) {
		int index = findAmpersand(args);
		if (index != -1) {
			args[index - 1] = 0;
		}
		
		execvp(args[0], args);
	} else if (pid > 0) {
		if (findAmpersand(args) == -1) {
			while (pid != wait(0));
		}
	}
}

int findAmpersand(char **args) {
	int counter = 0;
	while (args[counter]) {
		if (strstr(args[counter++], "&")) {
			return counter;
		}
	}
	
	return -1;
}

void displayHistory(DArray *historyArray) {
	char *command = 0;
	int historySize = sizeDArray(historyArray);
	int n = min(historySize, 10);
	
	for (int i = historySize - n; i < historySize; i++) {
		command = getDArray(historyArray, i);
		printf("%d %s", historySize - i + (historySize - n), command);
	}
}

int min(int a, int b) {
	return a > b ? b : a;
}

void execHistory(DArray *historyArray, int index) {
	int historySize = sizeDArray(historyArray);
	char *command = getDArray(historyArray, historySize - index);
	if (strcmp(command, "history\n")) {
		char **args = buildArgs(command);
		runArgs(args);
	} else {
		displayHistory(historyArray);
	}
}

int parseInt(char *src) {
	long length = strlen(src);
	
	if (length > 2) {
		char *str = src + 1;
		str[length - 1] = 0;
		
		return atoi(str);
	}
	
	return 0;
}

