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

rcfftopExP:	rcfftopEx.c
	$(COMPILEP) -o rcfftopEx rcfftopEx.c $(librariesP)

rcfftopExD:	rcfftopEx.c
	$(COMPILED) -o rcfftopEx rcfftopEx.c $(librariesD)

clean:
	rm -f rcfftopEx *.exe
