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
SOURCES= vsip_cmcopy_d_d.c \
vsip_cvcopy_d_d.c \
vsip_mcopy_d_d.c \
vsip_vcopy_bl_d.c \
vsip_vcopy_d_bl.c \
vsip_vcopy_d_d.c \
vsip_vcopy_d_f.c \
vsip_vcopy_d_i.c \
vsip_vcopy_f_d.c \
vsip_vcopy_i_d.c

OBJECTS= vsip_cmcopy_d_d.o \
vsip_cvcopy_d_d.o \
vsip_mcopy_d_d.o \
vsip_vcopy_bl_d.o \
vsip_vcopy_d_bl.o \
vsip_vcopy_d_d.o \
vsip_vcopy_d_f.o \
vsip_vcopy_d_i.o \
vsip_vcopy_f_d.o \
vsip_vcopy_i_d.o

$(ARCHIVE):	$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
