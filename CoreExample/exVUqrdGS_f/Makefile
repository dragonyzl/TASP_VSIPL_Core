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

all:	vsipqrdex qrdex

vsipqrdex:	vsipqrdex.c
	$(COMPILEP) -o vsipqrdex vsipqrdex.c $(librariesP)

qrdex:	qrdex.c
	$(COMPILEP) -o qrdex qrdex.c $(librariesP)

development:	vsipqrdex.c
	$(COMPILED) -o vsipqrdex vsipqrdex.c $(librariesD)

clean:
	rm -f qrdex vsipqrdex *.exe
