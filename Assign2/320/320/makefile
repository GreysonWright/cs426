OBJS = main.o PIDManager.o
OPTS = -Wall -g -std=c99 -Wextra

320 : $(OBJS)
		gcc $(OPTS) $(OBJS) -o 320 -lm

main.o : main.c
		gcc $(OPTS) -c main.c

PIDManager.o : PIDManager.c PIDManager.h
		gcc $(OPTS) -c PIDManager.c

clean :
		rm -f $(OBJS) 320

test :	./320
		./320
		
