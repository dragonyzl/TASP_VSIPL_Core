## RJudd October 11, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../../include -I../../../include/privateC
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-O2 -Wall -ansi -pedantic -fopenmp
AR=ar
AR_OPTIONS=rcvs
ARLIB=libvsip_c.a
ARCHIVE=../../../lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES=vsip_cvcopy_f_f.c \
vsip_vcopy_bl_bl.c \
vsip_vcopy_bl_f.c \
vsip_vcopy_f_bl.c \
vsip_vcopy_f_f.c \
vsip_vcopy_f_i.c \
vsip_vcopy_i_f.c \
vsip_vcopy_i_i.c \
vsip_vcopy_i_vi.c \
vsip_vcopy_mi_mi.c \
vsip_vcopy_vi_i.c \
vsip_vcopy_vi_vi.c \
vsip_mcopy_f_f.c \
vsip_cmcopy_f_f.c

OBJECTS=vsip_cvcopy_f_f.o \
vsip_vcopy_bl_bl.o \
vsip_vcopy_bl_f.o \
vsip_vcopy_f_bl.o \
vsip_vcopy_f_f.o \
vsip_vcopy_f_i.o \
vsip_vcopy_i_f.o \
vsip_vcopy_i_i.o \
vsip_vcopy_i_vi.o \
vsip_vcopy_mi_mi.o \
vsip_vcopy_vi_i.o \
vsip_vcopy_vi_vi.o \
vsip_mcopy_f_f.o \
vsip_cmcopy_f_f.o

$(ARCHIVE):	$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
