## created by RJudd for Core Lite
## SPAWARSYSCEN D881 
## October 11, 1998

CC=gcc
INCLUDE=-I../../../../../include -I../../../../../include/privateC
DEFINES=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIB=libDvsip_c.a
ARCHIVE=../../../../../lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES= vsip_mcheck_markings.c \
vsip_mcheck_outside.c \
vsip_vcheck_lengths_mi.c \
vsip_vcheck_outside_mi.c \
vsip_vcheck_valid_mi.c \
vsip_vcheck_lengths_bl_mi.c
OBJECTS= vsip_mcheck_markings.o \
vsip_mcheck_outside.o \
vsip_vcheck_lengths_mi.o \
vsip_vcheck_outside_mi.o \
vsip_vcheck_valid_mi.o \
vsip_vcheck_lengths_bl_mi.o

$(ARCHIVE):	$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
