## RJudd February 16, 1999 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../../include -I../../../include/privateC
DEFINES=-DVSIP_PERFORMANCE_MODE
DEFINESD=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIB=libvsip_c.a
ARLIBD=libDvsip_c.a
ARCHIVE=../../../lib/$(ARLIB)
ARCHIVED=../../../lib/$(ARLIBD)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
COMPILED=$(CC) $(DEFINESD) $(OPTIONS)
SOURCES= vsip_mprod_d.c \
vsip_mprodt_d.c \
vsip_mtrans_d.c \
vsip_mvprod_d.c \
vsip_vmprod_d.c \
vsip_vouter_d.c \
vsip_gemp_d.c \
vsip_gems_d.c
OBJECTS= vsip_mprod_d.o \
vsip_mprodt_d.o \
vsip_mtrans_d.o \
vsip_mvprod_d.o \
vsip_vmprod_d.o \
vsip_vouter_d.o \
vsip_gemp_d.o \
vsip_gems_d.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

development:	archd

objd:	$(SOURCES)
	$(COMPILED) $(INCLUDE) -c $(SOURCES)

archd:	objd
	$(AR) $(AR_OPTIONS) $(ARCHIVED) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
