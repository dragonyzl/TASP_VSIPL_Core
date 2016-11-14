## Created RJudd January 31, 1999 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../include
DEFINEP=-DVSIP_PERFORMANCE_MODE
DEFINED=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
LIBRARY=-L../../lib
librariesP=-lvsip_c -lm 
librariesD=-lDvsip_c -lm
COMPILEP=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINEP) $(OPTIONS)
COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINED) $(OPTIONS)

example13:	example13.c
	$(COMPILEP) -o example13 example13.c $(librariesP)

development:	example13.c
	$(COMPILED) -o example13 example13.c $(librariesD)

clean:
	rm -f example13 *.exe
