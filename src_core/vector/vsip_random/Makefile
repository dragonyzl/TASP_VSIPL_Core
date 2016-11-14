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
SOURCES=vsip_randcreate.c\
vsip_randdestroy.c\
vsip_randu_f.c \
vsip_vrandu_f.c \
vsip_randn_f.c \
vsip_vrandn_f.c \
vsip_crandn_f.c \
vsip_cvrandn_f.c \
vsip_crandu_f.c \
vsip_cvrandu_f.c

OBJECTS=vsip_randcreate.o\
vsip_randdestroy.o\
vsip_randu_f.o \
vsip_vrandu_f.o \
vsip_randn_f.o \
vsip_vrandn_f.o \
vsip_crandn_f.o \
vsip_cvrandn_f.o \
vsip_crandu_f.o \
vsip_cvrandu_f.o

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
