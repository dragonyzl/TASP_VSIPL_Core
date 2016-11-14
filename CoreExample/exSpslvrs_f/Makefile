## RJudd January 9, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../include
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-Wall -ansi -pedantic  -O2
LIBRARY=-L../../lib
libraries= -lvsip_c -lm

COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)

all: llsqsolEx


llsqsolEx:	llsqsolEx.c
	$(COMPILE) -o llsqsolEx llsqsolEx.c $(libraries)

clean:
	rm -f llsqsolEx *~ *.exe
