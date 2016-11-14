## Created RJudd June 16, 1999 
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

example14:	example14.c
	$(COMPILEP) -o example14 example14.c $(librariesP)

development:	example14.c
	$(COMPILED) -o example14 example14.c $(librariesD)

clean:
	rm -f example14 *.exe
