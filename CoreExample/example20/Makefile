## Created RJudd March 17, 1999 
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

all:	example20

example20:	example20.c
	$(COMPILEP) -o example20 example20.c $(librariesP)

development:	example20D

example20D:	example20.c
	$(COMPILED) -o example20 example20.c $(librariesD)

clean:
	rm -f example20 *.exe

cleanfiles:
	rm -f *.eps Freq_Resp_Kaiser conv_dec3 fir_dec3 kaiser_window fir_dec1 conv_dec1
