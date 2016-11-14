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

all:	cqrd2Ex cqrdEx qrd2Ex qrdEx

development:	cqrd2ExD cqrdExD qrd2ExD qrdExD

cqrdEx:	cqrdEx.c
	$(COMPILE) -o cqrdEx cqrdEx.c $(libraries)

qrdEx:	qrdEx.c
	$(COMPILE) -o qrdEx qrdEx.c $(libraries)

cqrd2Ex:	cqrd2Ex.c
	$(COMPILE) -o cqrd2Ex cqrd2Ex.c $(libraries)

qrd2Ex:	qrd2Ex.c
	$(COMPILE) -o qrd2Ex qrd2Ex.c $(libraries)

cqrdExD:	cqrdEx.c
	$(COMPILED) -o cqrdEx cqrdEx.c $(librariesD)

qrdExD:	qrdEx.c
	$(COMPILED) -o qrdEx qrdEx.c $(librariesD)

cqrd2ExD:	cqrd2Ex.c
	$(COMPILED) -o cqrd2Ex cqrd2Ex.c $(librariesD)

qrd2ExD: 	qrd2Ex.c
	$(COMPILED) -o qrd2Ex qrd2Ex.c $(librariesD)
 
clean:
	rm -f cqrd2Ex cqrdEx qrd2Ex qrdEx
