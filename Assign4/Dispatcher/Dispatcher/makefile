OBJS = dispatcher.o scanner.o sll.o queue.o job.o
OPTS = -Wall -g -std=c99 -Wextra

dispatcher : $(OBJS)
		gcc $(OPTS) $(OBJS) -o dispatcher

dispatcher.o : dispatcher.c
		gcc $(OPTS) -c dispatcher.c

scanner.o : scanner.c scanner.h
		gcc $(OPTS) -c scanner.c

sll.o : sll.c sll.h
		gcc $(OPTS) -c sll.c

queue.o : queue.c queue.h
		gcc $(OPTS) -c queue.c

job.o : job.c job.h
		gcc $(OPTS) -c job.c

clean :
		rm -f $(OBJS) dispatcher

test :	./dispatcher
		./dispatcher input.txt
		
