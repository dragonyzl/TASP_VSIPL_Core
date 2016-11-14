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

example15:	example15.c
	$(COMPILEP) -o example15 example15.c $(librariesP)

development:	example15.c
	$(COMPILED) -o example15 example15.c $(librariesD)

clean:
	rm -f example15 *.exe
