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

llsqExP:	llsqEx.c
	$(COMPILEP) -o llsqEx llsqEx.c $(librariesP)

development:	llsqEx.c
	$(COMPILED) -o llsqEx llsqEx.c $(librariesD)

clean:
	rm -f llsqEx *.exe
