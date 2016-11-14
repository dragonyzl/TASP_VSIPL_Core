CC=gcc
INCLUDE=-I../../include
DEFINEP=-DVSIP_PERFORMANCE_MODE
DEFINED=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic 
LIBRARY=-L../../lib
librariesP=-lvsip_c -lm -lVU_c
librariesD=-lDvsip_c -lm
COMPILEP=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINEP) $(OPTIONS)
COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINED) $(OPTIONS)

all:	llsqExP qrdsolrExP
development:	llsqExD qrdsolrExD

qrdsolrExP:	qrdsolrEx.c
	$(COMPILEP) -o qrdsolrEx qrdsolrEx.c $(librariesP)

llsqExP:	llsqEx.c
	$(COMPILEP) -o llsqEx llsqEx.c $(librariesP)

qrdsolrExD:	qrdsolrEx.c
	$(COMPILED) -o qrdsolrEx qrdsolrEx.c $(librariesD)

llsqExD:	llsqEx.c
	$(COMPILED) -o llsqEx llsqEx.c $(librariesD)

clean:
	rm -f llsqEx qrdsolrEx *.exe
