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

all:	crandomEx nrandomEx randomEx

nrandomEx:	nrandomEx.c
	$(COMPILEP) -o nrandomEx nrandomEx.c $(librariesP)

crandomEx:	crandomEx.c
	$(COMPILEP) -o crandomEx crandomEx.c $(librariesP)

randomEx:	randomEx.c
	$(COMPILEP) -o randomEx randomEx.c $(librariesP)

development:	crandomExE nrandomExD randomExD

nrandomExD:	nrandomEx.c
	$(COMPILED) -o nrandomEx nrandomEx.c $(librariesD)

crandomExD:	crandomEx.c
	$(COMPILED) -o crandomEx crandomEx.c $(librariesD)

randomExD:	randomEx.c
	$(COMPILED) -o randomEx randomEx.c $(librariesD)

clean:
	rm -f crandomEx nrandomEx randomEx
