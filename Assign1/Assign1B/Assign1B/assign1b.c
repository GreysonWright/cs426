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
int interpretInput(char *, DArray *);
char **buildArgs(char *);
void execArgs(char **);
int findAmpersand(char **);
void displayHistory(DArray *);
int max(int, int);
int parseInt(char *);
void execHistory(DArray *, int);

int main(void) {
	int should_run = 1;
	DArray *historyArray = newDArray(0);
	
	while (should_run) {
		printf("osh>");
		fflush(stdout);
		
		char *input = readLine(stdin);
		should_run = interpretInput(input, historyArray);
	}
	return 0;
}

int interpretInput(char *input, DArray *historyArray) {
	char **args = 0;
	
	if (!strcmp(input, "exit\n")) {
		return 0;
	}
	
	if (!strcmp(input, "history\n")) {
		if (sizeDArray(historyArray) > 0) {
			displayHistory(historyArray);
		} else {
			printf("No commands in history.\n");
		}
		return 1;
	}
	
	if (!strcmp(input, "!!\n")) {
		if (sizeDArray(historyArray) > 0) {
			int historySize = sizeDArray(historyArray);
			execHistory(historyArray, historySize);
		} else {
			printf("No commands in history.\n");
		}
		return 1;
	}
	
	if (input[0] == '!') {
		int parsedInt = parseInt(input);
		if (parsedInt > 0 && sizeDArray(historyArray) >= parsedInt) {
			execHistory(historyArray, parsedInt);
		} else {
			printf("No such command in history.\n");
		}
		return 1;
	}
	
	if (!isspace(input[0])) {
		args = buildArgs(input);
		execArgs(args);
		insertDArray(historyArray, input);
		return 1;
	}
	return 1;
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

void execArgs(char **args) {
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
	int n = max(historySize - 10, 0);
	
	for (int i = historySize - 1; i >= n; i--) {
		command = getDArray(historyArray, i);
		printf("%d %s", i + 1, command);
	}
}

int max(int a, int b) {
	return a > b ? a : b;
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

void execHistory(DArray *historyArray, int index) {
	char *command = getDArray(historyArray, index - 1);
	char **args = buildArgs(command);
	execArgs(args);
}
