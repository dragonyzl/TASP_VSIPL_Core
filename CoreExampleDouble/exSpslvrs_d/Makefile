## RJudd January 9, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../include
DEFINES=-DVSIP_PERFORMANCE_MODE
DEFINESD=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-Wall -ansi -pedantic  -O2
LIBRARY=-L../../lib
libraries= -lvsip_c -lm
librariesD= -lDvsip_c -lm

COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)
COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINESD) $(OPTIONS)

all: llsqsolEx
development: llsqsolExD 

llsqsolEx:	llsqsolEx.c
	$(COMPILE) -o llsqsolEx llsqsolEx.c $(libraries)

llsqsolExD:	llsqsolEx.c
	$(COMPILED) -o llsqsolEx llsqsolEx.c $(librariesD)

clean:
	rm -f llsqsolEx *~ *.exe
