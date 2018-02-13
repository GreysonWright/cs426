#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "integer.h"

//extern void Fatal(char *,...);

integer *
newInteger(int x)
    {
    integer *p = malloc(sizeof(integer));
//    if (p == 0) Fatal("out of memory\n");
    p->value = x;
    return p;
    }

int 
getInteger(integer *v)
    {
    return v->value;
    }

int 
setInteger(integer *v,int x)
    {
    int old = v->value;
    v->value = x;
    return old;
    }

void 
displayInteger(FILE *fp,void *v)
    {
    fprintf(fp,"%d",getInteger((integer *) v));
    }

int
compareInteger(void *v,void *w)
    {
    return ((integer *) v)->value - ((integer *) w)->value;
    }

void
freeInteger(integer *v)
    {
	v->value = 0;
    free(v);
    }
