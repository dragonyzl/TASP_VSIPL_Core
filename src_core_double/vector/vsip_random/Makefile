## RJudd December 8, 1998 
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
SOURCES=vsip_randu_d.c \
vsip_vrandu_d.c \
vsip_randn_d.c \
vsip_vrandn_d.c \
vsip_crandn_d.c \
vsip_cvrandn_d.c \
vsip_crandu_d.c \
vsip_cvrandu_d.c

OBJECTS= vsip_randu_d.o \
vsip_vrandu_d.o \
vsip_randn_d.o \
vsip_vrandn_d.o \
vsip_crandn_d.o \
vsip_cvrandn_d.o \
vsip_crandu_d.o \
vsip_cvrandu_d.o

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
