## Created RJudd
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

all:	outerEx couterEx

outerEx:	outerEx.c
	$(COMPILEP) -o outerEx outerEx.c $(librariesP)

couterEx:	couterEx.c
	$(COMPILEP) -o couterEx couterEx.c $(librariesP)

clean:
	rm -f couterEx outerEx *.exe
