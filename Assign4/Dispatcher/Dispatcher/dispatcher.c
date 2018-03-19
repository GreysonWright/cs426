//
//  main.c
//  Dispatcher
//
//  Created by Greyson Wright on 3/16/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

int main(int argc, const char **argv) {
//	FILE *file = fopen(argv[1], "r");
	char str[10];
	char * c = fgets(str, 10, stdin);
	printf("%s\n", c);
	return 0;
}
