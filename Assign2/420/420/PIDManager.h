//
//  PIDManager.h
//  320
//
//  Created by Greyson Wright on 2/13/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#ifndef PIDManager_h
#define PIDManager_h

#include <stdio.h>
#include <stdlib.h>

typedef struct PIDManager PIDManager;

PIDManager *newPIDManager(int);
int createProcess(PIDManager *);
int removeProcess(PIDManager *, int);

#endif /* PIDManager_h */
