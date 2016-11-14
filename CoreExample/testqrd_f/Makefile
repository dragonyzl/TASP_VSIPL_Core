CC=gcc
INCLUDE=-I../../include
DEFINEP=-DVSIP_PERFORMANCE_MODE
DEFINED=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic 
LIBRARY=-L../../lib
librariesP=-lVU_c -lvsip_c -lm
librariesD=-lVU_c -lDvsip_c -lm
COMPILEP=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINEP) $(OPTIONS)
COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINED) $(OPTIONS)

testqrd:	testqrd.c
	$(COMPILEP) -o testqrd testqrd.c $(librariesP)

development:	testqrd.c
	$(COMPILED) -o testqrd testqrd.c $(librariesD)

clean:
	rm -f testqrd testqrd *.exe
