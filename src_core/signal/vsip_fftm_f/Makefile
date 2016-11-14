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
SOURCES= vsip_fftm_destroy_f.c \
vsip_ccfftmop_create_f.c \
vsip_ccfftmop_f.c \
vsip_ccfftmip_create_f.c \
vsip_ccfftmip_f.c \
vsip_rcfftmop_f.c \
vsip_rcfftmop_create_f.c \
vsip_crfftmop_f.c \
vsip_crfftmop_create_f.c \
vsip_fftm_getattr_f.c
OBJECTS= vsip_fftm_destroy_f.o \
vsip_ccfftmop_create_f.o \
vsip_ccfftmop_f.o \
vsip_ccfftmip_create_f.o \
vsip_ccfftmip_f.o \
vsip_rcfftmop_f.o \
vsip_rcfftmop_create_f.o \
vsip_crfftmop_f.o \
vsip_crfftmop_create_f.o \
vsip_fftm_getattr_f.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
