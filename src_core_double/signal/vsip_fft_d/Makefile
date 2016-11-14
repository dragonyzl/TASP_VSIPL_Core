## RJudd October 11, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../../include -I../../../include/privateC
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIB=libvsip_c.a
ARCHIVE=../../../lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES= vsip_fft_destroy_d.c \
vsip_ccfftop_create_d.c \
vsip_ccfftop_d.c \
vsip_rcfftop_create_d.c \
vsip_rcfftop_d.c \
vsip_crfftop_create_d.c \
vsip_crfftop_d.c \
vsip_ccfftip_create_d.c \
vsip_ccfftip_d.c \
vsip_fft_getattr_d.c 
OBJECTS= vsip_fft_destroy_d.o \
vsip_ccfftop_create_d.o \
vsip_ccfftop_d.o \
vsip_rcfftop_create_d.o \
vsip_rcfftop_d.o \
vsip_crfftop_create_d.o \
vsip_crfftop_d.o \
vsip_ccfftip_create_d.o \
vsip_ccfftip_d.o \
vsip_fft_getattr_d.o 

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
