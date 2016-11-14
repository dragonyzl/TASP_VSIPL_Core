## Created RJudd to make add example for Core Lite, October 11, 1998 
## SPAWARSYSCEN D881

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

all:	ctoeplitzEx toeplitzEx
development: ctoeplitzExD toeplitzExD

ctoeplitzEx : ctoeplitzEx.c
	$(COMPILEP) -o ctoeplitzEx ctoeplitzEx.c $(librariesP)

toeplitzEx : toeplitzEx.c
	$(COMPILEP) -o toeplitzEx toeplitzEx.c $(librariesP)

ctoeplitzExD : ctoeplitzEx.c
	$(COMPILED) -o ctoeplitzEx ctoeplitzEx.c $(librariesD)

toeplitzExD : toeplitzEx.c
	$(COMPILED) -o toeplitzEx toeplitzEx.c  $(librariesD)

clean:
	rm -f ctoeplitzEx  toeplitzEx
