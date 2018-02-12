#ifndef __DOUBLE_INCLUDED__
#define __DOUBLE_INCLUDED__

#include <stdio.h>

typedef struct DOUBLE {
    double value;
} Double;

extern Double *newDouble(double);
extern double getDouble(Double *);
extern double setDouble(Double *,double);
extern void displayDouble(FILE *,void *);
extern double compareDouble(void *,void *);
extern void freeDouble(Double *);

#define PINFINITY IN_MAX
#define NINFINITY IN_MIN

#endif
