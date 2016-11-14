## RJudd October 11, 1998 
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
SOURCES= vsip_cmalldestroy_f.c \
vsip_cmbind_f.c \
vsip_cmcloneview_f.c \
vsip_cmcolview_f.c \
vsip_cmcreate_f.c \
vsip_cmdestroy_f.c \
vsip_cmdiagview_f.c \
vsip_cmget_f.c \
vsip_cmgetattrib_f.c \
vsip_cmgetblock_f.c \
vsip_cmgetcollength_f.c \
vsip_cmgetcolstride_f.c \
vsip_cmgetoffset_f.c \
vsip_cmgetrowlength_f.c \
vsip_cmgetrowstride_f.c \
vsip_cmput_f.c \
vsip_cmputattrib_f.c \
vsip_cmputcollength_f.c \
vsip_cmputcolstride_f.c \
vsip_cmputoffset_f.c \
vsip_cmputrowlength_f.c \
vsip_cmputrowstride_f.c \
vsip_cmrowview_f.c \
vsip_cmsubview_f.c \
vsip_cmtransview_f.c \
vsip_mimagview_f.c \
vsip_mrealview_f.c

OBJECTS= vsip_cmalldestroy_f.o \
vsip_cmbind_f.o \
vsip_cmcloneview_f.o \
vsip_cmcolview_f.o \
vsip_cmcreate_f.o \
vsip_cmdestroy_f.o \
vsip_cmdiagview_f.o \
vsip_cmget_f.o \
vsip_cmgetattrib_f.o \
vsip_cmgetblock_f.o \
vsip_cmgetcollength_f.o \
vsip_cmgetcolstride_f.o \
vsip_cmgetoffset_f.o \
vsip_cmgetrowlength_f.o \
vsip_cmgetrowstride_f.o \
vsip_cmput_f.o \
vsip_cmputattrib_f.o \
vsip_cmputcollength_f.o \
vsip_cmputcolstride_f.o \
vsip_cmputoffset_f.o \
vsip_cmputrowlength_f.o \
vsip_cmputrowstride_f.o \
vsip_cmrowview_f.o \
vsip_cmsubview_f.o \
vsip_cmtransview_f.o \
vsip_mimagview_f.o \
vsip_mrealview_f.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
