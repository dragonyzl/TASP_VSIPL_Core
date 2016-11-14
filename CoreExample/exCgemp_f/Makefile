## CREATED RJudd January 30, 1999
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../include 
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
LIBRARY=-L../../lib
libraries=-lvsip_c \
           -lm
COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)
OBJECTS = cgempEx cgempNTEx cgempTNEx cgempTTEx cgempNHEx cgempHNEx cgempHHEx cgempCHEx cgempHCEx cgempCCEx

all:	$(OBJECTS)

cgempEx:	cgempEx.c
	$(COMPILE) -o cgempEx cgempEx.c $(libraries)

cgempNTEx:	cgempNTEx.c
	$(COMPILE) -o cgempNTEx cgempNTEx.c $(libraries)

cgempTNEx:	cgempTNEx.c
	$(COMPILE) -o cgempTNEx cgempTNEx.c $(libraries)

cgempTTEx:	cgempTTEx.c
	$(COMPILE) -o cgempTTEx cgempTTEx.c $(libraries)

cgempNHEx:	cgempNHEx.c
	$(COMPILE) -o cgempNHEx cgempNHEx.c $(libraries)

cgempHNEx:	cgempHNEx.c
	$(COMPILE) -o cgempHNEx cgempHNEx.c $(libraries)

cgempHHEx:	cgempHHEx.c
	$(COMPILE) -o cgempHHEx cgempHHEx.c $(libraries)

cgempCHEx:	cgempCHEx.c
	$(COMPILE) -o cgempCHEx cgempCHEx.c $(libraries)

cgempHCEx:	cgempHCEx.c
	$(COMPILE) -o cgempHCEx cgempHCEx.c $(libraries)

cgempCCEx:	cgempCCEx.c
	$(COMPILE) -o cgempCCEx cgempCCEx.c $(libraries)

clean:
	rm -f $(OBJECTS) *.exe
