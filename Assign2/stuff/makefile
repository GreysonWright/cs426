OBJS420 = 420.o PIDManager.o PIDInterface.o
OPTS420 = -lpthread -Wall -g -std=c99 -Wextra
OBJS421 = 421.o darray.o integer.o
OPTS421 = -lpthread -Wall -g -std=c99 -Wextra

all : 420 421

420 : $(OBJS420)
		gcc $(OPTS420) $(OBJS420) -o 420 -lm

420.o : 420.c
		gcc $(OPTS420) -c 420.c

PIDManager.o : PIDManager.c PIDManager.h
		gcc $(OPTS420) -c PIDManager.c

PIDInterface.o : PIDInterface.c PIDInterface.h
		gcc $(OPTS420) -c PIDInterface.c

421 : $(OBJS421)
		gcc $(OPTS421) $(OBJS421) -o 421 -lm

421.o : 421.c
		gcc $(OPTS421) -c 421.c

darray.o : darray.c darray.h
		gcc $(OPTS421) -c darray.c

integer.o : integer.c integer.h
		gcc $(OPTS421) -c integer.c

clean :
		rm -f $(OBJS420) $(OBJS421) 420 421
