#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Double.h"

//extern void Fatal(char *,...);

Double *
newDouble(double x)
    {
    Double *p = malloc(sizeof(Double));
//    if (p == 0) Fatal("out of memory\n");
    p->value = x;
    return p;
    }

double
getDouble(Double *v)
    {
    return v->value;
    }

double
setDouble(Double *v,double x)
    {
    double old = v->value;
    v->value = x;
    return old;
    }

void 
displayDouble(FILE *fp,void *v)
    {
    fprintf(fp,"%lf",getDouble((Double *) v));
    }

double
compareDouble(void *v,void *w)
    {
    return ((Double *) v)->value - ((Double *) w)->value;
    }

void
freeDouble(Double *v)
    {
	v->value = 0;
    free(v);
    }
