## Created RJudd to make add example for Core Lite, October 11, 1998 
## SPAWARSYSCEN D881

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
SOURCES= VU_printstdout_f.c \
VU_scanstdin_f.c \
VU_cprintstdout_f.c \
VU_cscanstdin_f.c
OBJECTS= VU_printstdout_f.o \
VU_scanstdin_f.o \
VU_cprintstdout_f.o \
VU_cscanstdin_f.o

all:	$(OBJECTS) firEx cfirEx 

firEx : firEx.c
	$(COMPILEP) -o firEx firEx.c $(OBJECTS) $(librariesP)

cfirEx : cfirEx.c
	$(COMPILEP) -o cfirEx cfirEx.c $(OBJECTS) $(librariesP)

$(OBJECTS) : $(SOURCES)
	$(COMPILED) -c $(SOURCES)

clean:
	rm -f firEx cfirEx $(OBJECTS) *.exe
