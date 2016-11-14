## RJudd January 9, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../include -I../../include/private
DEFINES=-DVSIP_PERFORMANCE_MODE
DEFINESD=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-Wall -ansi -pedantic -O2 
LIBRARY=-L../../lib
libraries= -lvsip_c -lm
librariesD= -lDvsip_c -lm

COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)
COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINESD) $(OPTIONS)

all: choldEx ccholdEx

development:	choldExD ccholdExD

choldEx:	choldEx.c
	$(COMPILE) -o choldEx choldEx.c $(libraries)

ccholdEx:	ccholdEx.c
	$(COMPILE) -o ccholdEx ccholdEx.c $(libraries)

choldExD:	choldEx.c
	$(COMPILED) -o choldEx choldEx.c $(librariesD)

ccholdExD:	ccholdEx.c
	$(COMPILED) -o ccholdEx ccholdEx.c $(librariesD)

clean:
	rm -f choldEx ccholdEx *.exe
