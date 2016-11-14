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

qrdsolrExP:	qrdsolrEx.c
	$(COMPILEP) -o qrdsolrEx qrdsolrEx.c $(librariesP)

qrdsolrExD:	qrdsolrEx.c
	$(COMPILED) -o qrdsolrEx qrdsolrEx.c $(librariesD)

clean:
	rm -f qrdsolrEx *.exe
