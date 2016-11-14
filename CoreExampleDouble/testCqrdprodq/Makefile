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
all:	testCqrdprodq testCqrdprodq1

testCqrdprodq:	testCqrdprodq.c
	$(COMPILEP) -o testCqrdprodq testCqrdprodq.c $(librariesP)

testCqrdprodq1:	testCqrdprodq1.c
	$(COMPILEP) -o testCqrdprodq1 testCqrdprodq1.c $(librariesP)

development:	testCqrdprodq.c
	$(COMPILED) -o testCqrdprodq testCqrdprodq.c $(librariesD)

clean:
	rm -f testCqrdprodq testCqrdprodq1 *.exe
