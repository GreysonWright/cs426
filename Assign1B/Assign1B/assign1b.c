//
//  main.c
//  Assign1B
//
//  Created by Greyson Wright on 1/31/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE 80 /* The maximum length command */

void readArgs(char **);

int main(void) {
	char *args[MAX_LINE / 2 + 1];
	int should_run = 1;
	
	while (should_run) {
		printf("osh>");
		fflush(stdout);
		
		readArgs(args);
		
		if (!strcmp(args[0], "exit")) {
			should_run = 0;
		} else {
			
		}
		/**
		 * After reading user input, the steps are:
		 * (1) fork a child process using fork()
		 * (2) the child process will invoke execvp()
		 * (3) if command included &, parent will invoke wait() */
	}
	return 0;
}

void readArgs(char **args) {
	char *str = malloc(MAX_LINE + 1);
	fgets(str, MAX_LINE, stdin);
	
	char *token = strtok(str, " \n");
	int count = 0;
	while (token) {
		args[count++] = token;
		token = strtok(0, " \n");
	}
}
