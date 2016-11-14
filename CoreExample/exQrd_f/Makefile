## RJudd January 9, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../include
DEFINES=-DVSIP_PERFORMANCE_MODE
DEFINESD=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-Wall -ansi -pedantic  -O2
LIBRARY=-L../../lib
libraries= -lvsip_c -lm
librariesD= -lDvsip_c -lm

COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINESD) $(OPTIONS)
COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)

all: qrdEx qrd2Ex cqrdEx cqrd2Ex
development: qrdExD qrd2ExD cqrdExD cqrd2ExD

qrdEx:	qrdEx.c
	$(COMPILE) -o qrdEx qrdEx.c $(libraries)

qrd2Ex:	qrd2Ex.c
	$(COMPILE) -o qrd2Ex qrd2Ex.c $(libraries)

cqrdEx:	cqrdEx.c
	$(COMPILE) -o cqrdEx cqrdEx.c $(libraries)

cqrd2Ex: cqrd2Ex.c
	$(COMPILE) -o cqrd2Ex cqrd2Ex.c $(libraries)

qrdExD:	qrdEx.c
	$(COMPILED) -o qrdEx qrdEx.c $(librariesD)

qrd2_test:	qrd2_test.c
	$(COMPILED) -o qrd2_test qrd2_test.c -lVU_c $(librariesD) 

qrd2ExD:	qrd2Ex.c
	$(COMPILED) -o qrd2Ex qrd2Ex.c $(librariesD)

cqrdExD:	cqrdEx.c
	$(COMPILED) -o cqrdEx cqrdEx.c $(librariesD)

cqrd2ExD: cqrd2Ex.c
	$(COMPILED) -o cqrd2Ex cqrd2Ex.c $(librariesD)

clean:
	rm -f qrd2Ex qrdEx cqrd2Ex cqrdEx *~ *.exe
