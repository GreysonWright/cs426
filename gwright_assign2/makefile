OBJS320 = 320.o PIDManager.o p320.o
OPTS320 = -Wall -g -std=c99 -Wextra
OBJS420 = p420.o PIDManager.o p320.o
OPTS420 = -lpthread -Wall -g -std=c99 -Wextra
OBJS421 = p421.o darray.o integer.o

all : 320 p420 p421

320 : $(OBJS320)
		gcc $(OPTS320) $(OBJS320) -o 320 -lm

320.o : 320.c
		gcc $(OPTS320) -c 320.c

p420 : $(OBJS420)
		gcc $(OPTS420) $(OBJS420) -o p420 -lm

p420.o : p420.c
		gcc $(OPTS420) -c p420.c

PIDManager.o : PIDManager.c PIDManager.h
		gcc $(OPTS420) -c PIDManager.c

p320.o : p320.c p320.h
		gcc $(OPTS420) -c p320.c

p421 : $(OBJS421)
		gcc $(OPTS420) $(OBJS421) -o p421 -lm

p421.o : p421.c
		gcc $(OPTS420) -c p421.c

darray.o : darray.c darray.h
		gcc $(OPTS420) -c darray.c

integer.o : integer.c integer.h
		gcc $(OPTS420) -c integer.c

clean :
		rm -f $(OBJS320) $(OBJS420) $(OBJS421) p420 p421 320
