## RJudd January 9, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../include -I../../include/private
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-Wall -ansi -pedantic  -O2 
LIBRARY=-L../../lib
libraries= -lvsip_c -lm

COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)

all: choldEx ccholdEx

choldEx:	choldEx.c
	$(COMPILE) -o choldEx choldEx.c $(libraries)

ccholdEx:	ccholdEx.c
	$(COMPILE) -o ccholdEx ccholdEx.c $(libraries)

clean:
	rm -f choldEx ccholdEx *.exe
