## RJudd January 9, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../include -I../../include/private
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
LIBRARY=-L../../lib
libraries=-lVU_c -lvsip_c \
-lm

COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)

all: ludEx lud2Ex clud2Ex clud3Ex lud3Ex

ludEx:	ludEx.c
	$(COMPILE) -o ludEx ludEx.c $(libraries)

lud2Ex:	lud2Ex.c
	$(COMPILE) -o lud2Ex lud2Ex.c $(libraries)

clud2Ex:	clud2Ex.c
	$(COMPILE) -o clud2Ex clud2Ex.c $(libraries)

lud3Ex:	lud3Ex.c
	$(COMPILE) -o lud3Ex lud3Ex.c $(libraries)

clud3Ex:	clud3Ex.c
	$(COMPILE) -o clud3Ex clud3Ex.c $(libraries)

clean:
	rm -f clud3Ex lud3Ex ludEx lud2Ex clud2Ex *.exe
