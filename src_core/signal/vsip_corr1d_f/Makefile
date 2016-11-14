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
SOURCES= vsip_corr1d_create_f.c \
vsip_corr1d_destroy_f.c \
vsip_correlate1d_f.c  \
vsip_ccorr1d_create_f.c \
vsip_ccorr1d_destroy_f.c \
vsip_ccorrelate1d_f.c \
vsip_corr1d_getattr_f.c \
vsip_ccorr1d_getattr_f.c
OBJECTS= vsip_corr1d_create_f.o \
vsip_corr1d_destroy_f.o \
vsip_correlate1d_f.o  \
vsip_ccorr1d_create_f.o \
vsip_ccorr1d_destroy_f.o \
vsip_ccorrelate1d_f.o \
vsip_corr1d_getattr_f.o \
vsip_ccorr1d_getattr_f.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

development:	archd

objd:	$(SOURCES)
	$(COMPILED) $(INCLUDE) -c $(SOURCES)

archd:	objd
	$(AR) $(AR_OPTIONS) $(ARCHIVED) $(OBJECTS)


obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
