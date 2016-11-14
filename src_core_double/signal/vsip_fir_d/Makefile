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
SOURCES= vsip_fir_create_d.c \
vsip_fir_destroy_d.c \
vsip_fir_reset_d.c \
vsip_firflt_d.c \
vsip_cfir_create_d.c \
vsip_cfir_destroy_d.c \
vsip_cfir_reset_d.c \
vsip_cfirflt_d.c \
vsip_fir_getattr_d.c \
vsip_cfir_getattr_d.c
OBJECTS= vsip_fir_create_d.o \
vsip_fir_destroy_d.o \
vsip_fir_reset_d.o \
vsip_firflt_d.o \
vsip_cfir_create_d.o \
vsip_cfir_destroy_d.o \
vsip_cfir_reset_d.o \
vsip_cfirflt_d.o \
vsip_fir_getattr_d.o \
vsip_cfir_getattr_d.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
