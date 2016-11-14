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
SOURCES= vsip_fftm_destroy_d.c \
vsip_ccfftmop_create_d.c \
vsip_ccfftmop_d.c \
vsip_ccfftmip_create_d.c \
vsip_ccfftmip_d.c \
vsip_rcfftmop_d.c \
vsip_rcfftmop_create_d.c \
vsip_crfftmop_d.c \
vsip_crfftmop_create_d.c \
vsip_fftm_getattr_d.c
OBJECTS= vsip_fftm_destroy_d.o \
vsip_ccfftmop_create_d.o \
vsip_ccfftmop_d.o \
vsip_ccfftmip_create_d.o \
vsip_ccfftmip_d.o \
vsip_rcfftmop_d.o \
vsip_rcfftmop_create_d.o \
vsip_crfftmop_d.o \
vsip_crfftmop_create_d.o \
vsip_fftm_getattr_d.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
