OBJS = assign1b.o darray.o
OPTS = -Wall -g -std=c99 -Wextra

assign1b : $(OBJS)
		gcc $(OPTS) $(OBJS) -o assign1b -lm

assign1b.o : assign1b.c
		gcc $(OPTS) -c assign1b.c

darray.o : darray.c darray.h
		gcc $(OPTS) -c darray.c

clean :
		rm -f $(OBJS) assign1b

test :	./assign1b
		./assign1b
		
