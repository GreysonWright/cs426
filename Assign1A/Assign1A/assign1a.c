//
//  main.c
//  Assign1A
//
//  Created by Greyson Wright on 1/30/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char * argv[]) {
	int n = atoi(argv[1]);
	pid_t pid = 0;
	
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork Failed\n");
	} else if (pid == 0) {
		while (1) {
			if (n == 1) {
				printf("%d\n", n);
				break;
			}
			
			printf("%d, ", n);
			if (n % 2 == 0) {
				n /= 2;
			} else {
				n = 3 * n + 1;
			}
		}
	} else if (pid > 0) {
		wait(0);
	}
	
	return 0;
}
