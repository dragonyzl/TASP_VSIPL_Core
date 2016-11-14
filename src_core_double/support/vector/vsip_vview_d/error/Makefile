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
SOURCES= vsip_vcheck_clobber_d.c \
vsip_vcheck_lengths_d.c \
vsip_vcheck_outside_d.c \
vsip_vcheck_valid_d.c \
vsip_vcheck_lengths_bl_d.c
OBJECTS= vsip_vcheck_clobber_d.o \
vsip_vcheck_lengths_d.o \
vsip_vcheck_outside_d.o \
vsip_vcheck_valid_d.o \
vsip_vcheck_lengths_bl_d.o


$(ARCHIVE):	$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)

