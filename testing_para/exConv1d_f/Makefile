## Created RJudd March 17, 1999 
## SPAWARSYSCEN D881 
CC=gcc
INCLUDE=-I../../include
DEFINEP=-DVSIP_PERFORMANCE_MODE
DEFINED=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic -fopenmp
LIBRARY=-L../../lib
librariesP=-lVU_c -lvsip_c  -lm
librariesD=-lVU_c -lDvsip_c -lm
COMPILEP=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINEP) $(OPTIONS)
COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINED) $(OPTIONS)

test: test1 test2 test3

conv1dEx:	conv1dEx.c
	$(COMPILEP) -o conv1dEx conv1dEx.c $(librariesP)
	$(COMPILEP) -o conv1dEx_para conv1dEx_para.c $(librariesP)

test1:	test1.c
	$(COMPILEP) -o test1 test1.c $(librariesP)

test2:	test2.c
	$(COMPILEP) -o test2 test2.c $(librariesP)

test3:	test3.c
	$(COMPILEP) -o test3 test3.c $(librariesP)

para:	conv1dEx_para.c
	$(COMPILEP) -o conv1dEx_para conv1dEx_para.c $(librariesP)

development:	conv1dExD

conv1dExD:	conv1dEx.c
	$(COMPILED) -o conv1dEx conv1dEx.c $(librariesD)

clean:
	rm -f conv1dEx *.exe
	rm -f conv1dEx_para *.exe
