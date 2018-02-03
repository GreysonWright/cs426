OBJS = assign1b.o dll.o stack.o
OPTS = -Wall -g -std=c99 -Wextra

assign1b : $(OBJS)
		gcc $(OPTS) $(OBJS) -o assign1b -lm

assign1b.o : assign1b.c
		gcc $(OPTS) -c assign1b.c

stack.o : stack.c stack.h
		gcc $(OPTS) -c stack.c

dll.o : dll.c dll.h
		gcc $(OPTS) -c dll.c

clean :
		rm -f $(OBJS) assign1b

test :	./assign1b
		./assign1b
		
