## Created RJudd to make add example for Core Lite, October 11, 1998 
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

test_some_stuffP:	test_some_stuff.c
	$(COMPILEP) -o test_some_stuff test_some_stuff.c $(librariesP)

test_some_stuffD:	test_some_stuff.c
	$(COMPILED) -o test_some_stuff test_some_stuff.c $(librariesD)

clean:
	rm -f test_some_stuff *.exe
