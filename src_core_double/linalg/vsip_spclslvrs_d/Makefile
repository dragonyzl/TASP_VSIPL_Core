## RJudd For Core March 28, 1998
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../../include -I../../../include/privateC
DEFINES=-DVSIP_PERFORMANCE_MODE
DEFINESD=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-Wall -ansi -pedantic -O2 
AR=ar
AR_OPTIONS=rcvs
ARLIB=libvsip_c.a
ARLIBD=libDvsip_c.a
ARCHIVE=../../../lib/$(ARLIB)
ARCHIVED=../../../lib/$(ARLIBD)
COMPILE=$(CC) $(INCLUDE) $(DEFINES) $(OPTIONS)
COMPILED=$(CC) $(DEFINESD) $(OPTIONS)

SOURCES= vsip_covsol_d.c \
vsip_ccovsol_d.c \
vsip_llsqsol_d.c \
vsip_cllsqsol_d.c \
vsip_toepsol_d.c \
vsip_ctoepsol_d.c

OBJECTS= vsip_covsol_d.o \
vsip_ccovsol_d.o \
vsip_llsqsol_d.o \
vsip_cllsqsol_d.o \
vsip_toepsol_d.o \
vsip_ctoepsol_d.o

$(ARCHIVE):	$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):     $(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

development:	archd

objd:	$(SOURCES)
	$(COMPILED) $(INCLUDE) -c $(SOURCES)

archd:	objd
	$(AR) $(AR_OPTIONS) $(ARCHIVED) $(OBJECTS)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
