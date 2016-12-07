## Created RJudd March 17, 1999 
## SPAWARSYSCEN D881 
CC=gcc
INCLUDE=-I../../include
DEFINEP=-DVSIP_PERFORMANCE_MODE
DEFINED=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic -fopenmp
LIBRARY=-L../../lib
librariesP=-lVU_c -lvsip_c  -lm
librariesD=-lVU_c -lDvsip_c -lm
COMPILEP=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINEP) $(OPTIONS)
COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINED) $(OPTIONS)

conv1dEx:	conv1dEx.c
	$(COMPILEP) -o conv1dEx conv1dEx.c $(librariesP)

development:	conv1dExD

conv1dExD:	conv1dEx.c
	$(COMPILED) -o conv1dEx conv1dEx.c $(librariesD)

clean:
	rm -f conv1dEx *.exe
