OBJS = main.o PIDManager.o PIDInterface.o
OPTS = -lpthread -Wall -g -std=c99 -Wextra

420 : $(OBJS)
		gcc $(OPTS) $(OBJS) -o 420 -lm

main.o : main.c
		gcc $(OPTS) -c main.c

PIDManager.o : PIDManager.c PIDManager.h
		gcc $(OPTS) -c PIDManager.c

PIDInterface.o : PIDInterface.c PIDInterface.h
		gcc $(OPTS) -c PIDInterface.c

clean :
		rm -f $(OBJS) 420

test :	./420
		./420
		
