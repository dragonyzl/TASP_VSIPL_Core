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
SOURCES= vsip_cchold_create_f.c \
vsip_cchold_destroy_f.c \
vsip_cchold_f.c \
vsip_cchold_getattr_f.c \
vsip_ccholsol_f.c \
vsip_chold_create_f.c \
vsip_chold_destroy_f.c \
vsip_chold_f.c \
vsip_chold_getattr_f.c \
vsip_cholsol_f.c
OBJECTS= vsip_cchold_create_f.o \
vsip_cchold_destroy_f.o \
vsip_cchold_f.o \
vsip_cchold_getattr_f.o \
vsip_ccholsol_f.o \
vsip_chold_create_f.o \
vsip_chold_destroy_f.o \
vsip_chold_f.o \
vsip_chold_getattr_f.o \
vsip_cholsol_f.o

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
