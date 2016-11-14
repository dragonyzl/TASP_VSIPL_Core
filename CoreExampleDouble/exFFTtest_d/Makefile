CC=gcc
INCLUDE=-I../../include
DEFINES=-DVSIP_PERFORMANCE_MODE
DEFINESD=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
LIBRARY=-L../../lib
libraries=-lVU_c -lvsip_c -lm
librariesD=-lVU_c -lDvsip_c -lm
COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)
COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINESD) $(OPTIONS)


ffttest:	ffttest.c
	$(COMPILE) -o ffttest ffttest.c $(libraries)

development:	ffttest.c
	$(COMPILED) -o ffttest ffttest.c $(librariesD)

clean:
	rm -f ffttest
