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

example17:	example17.c
	$(COMPILEP) -o example17 example17.c $(librariesP)

development:	example17.c
	$(COMPILED) -o example17 example17.c $(librariesD)

clean:
	rm -f example17 *.exe
