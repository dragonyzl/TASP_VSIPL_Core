## RJudd October 11, 1998 
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
SOURCES= vsip_cchold_create_d.c \
vsip_cchold_d.c \
vsip_cchold_destroy_d.c \
vsip_cchold_getattr_d.c \
vsip_ccholsol_d.c \
vsip_chold_create_d.c \
vsip_chold_d.c \
vsip_chold_destroy_d.c \
vsip_chold_getattr_d.c \
vsip_cholsol_d.c
OBJECTS= vsip_cchold_create_d.o \
vsip_cchold_d.o \
vsip_cchold_destroy_d.o \
vsip_cchold_getattr_d.o \
vsip_ccholsol_d.o \
vsip_chold_create_d.o \
vsip_chold_d.o \
vsip_chold_destroy_d.o \
vsip_chold_getattr_d.o \
vsip_cholsol_d.o

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
