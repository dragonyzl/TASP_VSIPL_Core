## created by RJudd for Core Lite
## SPAWARSYSCEN D881 
## October 11, 1998

CC=gcc
INCLUDE=-I../../include -I../../include/privateC
DEFINES=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIB=libDvsip_c.a
ARCHIVE=../../lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES= vsip_error_mask.c \
vsip_report_error.c \
vsip_vcheck_clobber.c \
vsip_vcheck_outside.c \
vsip_vcheck_markings.c
OBJECTS= vsip_error_mask.o \
vsip_report_error.o \
vsip_vcheck_clobber.o \
vsip_vcheck_outside.o \
vsip_vcheck_markings.o

$(ARCHIVE):	$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
