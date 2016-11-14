## Created RJudd March 17, 1999 
## SPAWARSYSCEN D881 
CC=gcc
INCLUDE=-I../../include
DEFINEP=-DVSIP_PERFORMANCE_MODE
DEFINED=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic 
LIBRARY=-L../../lib
librariesP=-lVU_c -lvsip_c  -lm
librariesD=-lVU_c -lDvsip_c -lm
COMPILEP=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINEP) $(OPTIONS)
COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINED) $(OPTIONS)

all:	example18

example18:	example18.c
	$(COMPILEP) -o example18 example18.c $(librariesP)

development:	example18D

example18D:	example18.c
	$(COMPILED) -o example18 example18.c $(librariesD)

clean:
	rm -f example18
