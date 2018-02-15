OBJS = main.o darray.o integer.o
OPTS = -lpthread -Wall -g -std=c99 -Wextra

421 : $(OBJS)
		gcc $(OPTS) $(OBJS) -o 421 -lm

main.o : main.c
		gcc $(OPTS) -c main.c

darray.o : darray.c darray.h
		gcc $(OPTS) -c darray.c

integer.o : integer.c integer.h
		gcc $(OPTS) -c integer.c

clean :
		rm -f $(OBJS) 421

test :	./421
		./421 90 81 78 95 79 72 85
		
