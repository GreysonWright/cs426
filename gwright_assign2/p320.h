//
//  PIDInterface.h
//
//  Created by Greyson Wright on 2/16/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#ifndef PIDInterface_h
#define PIDInterface_h

#include <stdio.h>
#include "PIDManager.h"

#define MIN_PID 300
#define MAX_PID 5000
#define MAX_MAP 4701

int allocate_map(void);
int allocate_pid(void);
void release_pid(int);

#endif /* PIDInterface_h */
