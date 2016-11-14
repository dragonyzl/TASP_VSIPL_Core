## Created RJudd February 15, 1999 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../../../include -I../../../../include/privateC
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIB=libvsip_c.a
ARCHIVE=../../../../lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES= vsip_cmalldestroy_d.c \
vsip_cmbind_d.c \
vsip_cmcloneview_d.c \
vsip_cmcolview_d.c \
vsip_cmcreate_d.c \
vsip_cmdestroy_d.c \
vsip_cmdiagview_d.c \
vsip_cmget_d.c \
vsip_cmgetattrib_d.c \
vsip_cmgetblock_d.c \
vsip_cmgetcollength_d.c \
vsip_cmgetcolstride_d.c \
vsip_cmgetoffset_d.c \
vsip_cmgetrowlength_d.c \
vsip_cmgetrowstride_d.c \
vsip_cmput_d.c \
vsip_cmputattrib_d.c \
vsip_cmputcollength_d.c \
vsip_cmputcolstride_d.c \
vsip_cmputoffset_d.c \
vsip_cmputrowlength_d.c \
vsip_cmputrowstride_d.c \
vsip_cmrowview_d.c \
vsip_cmsubview_d.c \
vsip_cmtransview_d.c \
vsip_mimagview_d.c \
vsip_mrealview_d.c

OBJECTS= vsip_cmalldestroy_d.o \
vsip_cmbind_d.o \
vsip_cmcloneview_d.o \
vsip_cmcolview_d.o \
vsip_cmcreate_d.o \
vsip_cmdestroy_d.o \
vsip_cmdiagview_d.o \
vsip_cmget_d.o \
vsip_cmgetattrib_d.o \
vsip_cmgetblock_d.o \
vsip_cmgetcollength_d.o \
vsip_cmgetcolstride_d.o \
vsip_cmgetoffset_d.o \
vsip_cmgetrowlength_d.o \
vsip_cmgetrowstride_d.o \
vsip_cmput_d.o \
vsip_cmputattrib_d.o \
vsip_cmputcollength_d.o \
vsip_cmputcolstride_d.o \
vsip_cmputoffset_d.o \
vsip_cmputrowlength_d.o \
vsip_cmputrowstride_d.o \
vsip_cmrowview_d.o \
vsip_cmsubview_d.o \
vsip_cmtransview_d.o \
vsip_mimagview_d.o \
vsip_mrealview_d.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
