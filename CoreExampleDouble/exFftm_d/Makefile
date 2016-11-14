## Created RJudd January 9, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../include
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
LIBRARY=-L../../lib
libraries=-lvsip_c -lm
COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)

all:	fftmEx fftmipEx rcfftmEx

fftmEx:	fftmEx.c
	$(COMPILE) -o fftmEx fftmEx.c $(libraries)

fftmipEx:	fftmipEx.c
	$(COMPILE) -o fftmipEx fftmipEx.c $(libraries)

rcfftmEx:	rcfftmEx.c
	$(COMPILE) -o rcfftmEx rcfftmEx.c $(libraries)

clean:
	rm -f rcfftmEx fftmEx fftmipEx *.exe
