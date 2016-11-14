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
all:	testQrdprodq testQrdprodq1

testQrdprodq:	testQrdprodq.c
	$(COMPILEP) -o testQrdprodq testQrdprodq.c $(librariesP)

testQrdprodq1:	testQrdprodq1.c
	$(COMPILEP) -o testQrdprodq1 testQrdprodq1.c $(librariesP)

development:	testQrdprodq.c
	$(COMPILED) -o testQrdprodq testQrdprodq.c $(librariesD)

clean:
	rm -f testQrdprodq testQrdprodq1 *.exe
