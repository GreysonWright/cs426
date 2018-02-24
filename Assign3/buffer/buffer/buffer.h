//
//  buffer.h
//  buffer
//
//  Created by Greyson Wright on 2/23/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#ifndef buffer_h
#define buffer_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>

#define BUFFER_SIZE 5
typedef int buffer_item;

int insert_item(buffer_item);
int remove_item(buffer_item *);

#endif /* buffer_h */
