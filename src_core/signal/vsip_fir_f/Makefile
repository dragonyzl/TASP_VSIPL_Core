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
SOURCES= vsip_fir_create_f.c \
vsip_fir_destroy_f.c \
vsip_firflt_f.c \
vsip_cfir_create_f.c \
vsip_cfir_destroy_f.c \
vsip_cfirflt_f.c \
vsip_fir_getattr_f.c \
vsip_cfir_getattr_f.c \
vsip_cfir_reset_f.c  \
vsip_fir_reset_f.c 
OBJECTS= vsip_fir_create_f.o \
vsip_fir_destroy_f.o \
vsip_firflt_f.o \
vsip_cfir_create_f.o \
vsip_cfir_destroy_f.o \
vsip_cfirflt_f.o \
vsip_fir_getattr_f.o \
vsip_cfir_getattr_f.o \
vsip_cfir_reset_f.o  \
vsip_fir_reset_f.o 

$(ARCHIVE): $(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS): $(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj: $(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
