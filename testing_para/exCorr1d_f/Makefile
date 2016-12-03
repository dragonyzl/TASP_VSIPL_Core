## Created RJudd March 17, 1999 
## SPAWARSYSCEN D881 
CC=gcc
INCLUDE=-I../../include
DEFINEP=-DVSIP_PERFORMANCE_MODE
DEFINED=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic -fopenmp
LIBRARY=-L../../lib
librariesP=-lVU_c -lvsip_c -lm
librariesD=-lVU_c -lDvsip_c -lm
COMPILEP=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINEP) $(OPTIONS)
COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINED) $(OPTIONS)

all:	corr1dEx ccorr1dEx cpara ccpara

corr1dEx:	corr1dEx.c
	$(COMPILEP) -o corr1dEx corr1dEx.c $(librariesP)

ccorr1dEx:	ccorr1dEx.c
	$(COMPILEP) -o ccorr1dEx ccorr1dEx.c $(librariesP)

cpara:	corr1dEx_para.c
	$(COMPILEP) -o corr1dEx_para corr1dEx_para.c $(librariesP)

ccpara:	ccorr1dEx_para.c
	$(COMPILEP) -o ccorr1dEx_para ccorr1dEx_para.c $(librariesP)

development:	corr1dExD ccorr1dExD

corr1dExD:	corr1dEx.c
	$(COMPILED) -o corr1dEx corr1dEx.c $(librariesD)

ccorr1dExD:	ccorr1dEx.c
	$(COMPILED) -o ccorr1dEx ccorr1dEx.c $(librariesD)

clean:
	rm -f ccorr1dEx corr1dEx *.exe
	rm -f ccorr1dEx_para corr1dEx_para *.exe
