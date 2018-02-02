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
#include "stack.h"
#define MAX_LINE 80 /* The maximum length command */

char *readArgs(char **);
void runArgs(char **);
void processString(char *, char **);
int findAmpersand(char **);

stack *historyStack;

int main(void) {
	char *args[MAX_LINE / 2 + 1];
	int should_run = 1;
	historyStack = newStack(0);
	
	while (should_run) {
		printf("osh>");
		fflush(stdout);
		
		char *input = readArgs(args);
		if (!strcmp(args[0], "exit")) {
			should_run = 0;
		} else if (!strcmp(args[0], "!!")) {
			char *lastInput = peekStack(historyStack);
			processString(lastInput, args);
			runArgs(args);
		} else if (strstr(args[0], "!")) {
			
		}  else {
			push(historyStack, input);
			runArgs(args);
		}
	}
	return 0;
}

char *readArgs(char **args) {
	char *str = malloc(MAX_LINE + 1);
	fgets(str, MAX_LINE, stdin);
	processString(str, args);
	return str;
}

void processString(char *str, char **args) {
	char *newString = malloc(MAX_LINE + 1);
	strcpy(newString, str);
	char *token = strtok(newString, " \n");
	int count = 0;
	while (token) {
		args[count++] = token;
		token = strtok(0, " \n");
	}
	args[count] = 0;
}

void runArgs(char **args) {
	pid_t pid = 0;
	
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork Failed\n");
	} else if (pid == 0) {
		int index = findAmpersand(args);
		if (index != -1) {
			args[index - 1] = 0;
		}
		
		execvp(args[0], args);
	} else if (pid > 0) {
		if (findAmpersand(args) != -1) {
			wait(0);
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
