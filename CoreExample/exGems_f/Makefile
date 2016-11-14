## CREATED RJudd January 31, 1999
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../include 
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
LIBRARY=-L../../lib
libraries=-lvsip_c \
           -lm
COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)
OBJECTS = cgemsCEx cgemsHEx cgemsTEx cgemsEx gemsEx gemsTEx 

all:	$(OBJECTS)

cgemsCEx:	cgemsCEx.c
	$(COMPILE) -o cgemsCEx cgemsCEx.c $(libraries)

cgemsHEx:	cgemsHEx.c
	$(COMPILE) -o cgemsHEx cgemsHEx.c $(libraries)

cgemsTEx:	cgemsTEx.c
	$(COMPILE) -o cgemsTEx cgemsTEx.c $(libraries)

cgemsEx:	cgemsEx.c
	$(COMPILE) -o cgemsEx cgemsEx.c $(libraries)

gemsEx:	gemsEx.c
	$(COMPILE) -o gemsEx gemsEx.c $(libraries)

gemsTEx:	gemsTEx.c
	$(COMPILE) -o gemsTEx gemsTEx.c $(libraries)

clean:
	rm -f $(OBJECTS) *.exe
