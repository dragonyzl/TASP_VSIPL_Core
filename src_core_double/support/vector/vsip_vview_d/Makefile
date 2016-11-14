## Created RJudd February 15, 1999
## SPAWARSYSCEN D881 
## For Core double

CC=gcc
INCLUDE=-I../../../../include -I../../../../include/privateC
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIB=libvsip_c.a
ARCHIVE=../../../../lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES= vsip_valldestroy_d.c \
vsip_vbind_d.c \
vsip_vcloneview_d.c \
vsip_vcreate_d.c \
vsip_vdestroy_d.c \
vsip_vget_d.c \
vsip_vgetattrib_d.c \
vsip_vgetblock_d.c \
vsip_vgetoffset_d.c \
vsip_vgetstride_d.c \
vsip_vgetlength_d.c \
vsip_vput_d.c \
vsip_vputattrib_d.c \
vsip_vputlength_d.c \
vsip_vputoffset_d.c \
vsip_vputstride_d.c \
vsip_vsubview_d.c
OBJECTS= vsip_valldestroy_d.o \
vsip_vbind_d.o \
vsip_vcloneview_d.o \
vsip_vcreate_d.o \
vsip_vdestroy_d.o \
vsip_vget_d.o \
vsip_vgetattrib_d.o \
vsip_vgetblock_d.o \
vsip_vgetoffset_d.o \
vsip_vgetstride_d.o \
vsip_vgetlength_d.o \
vsip_vput_d.o \
vsip_vputattrib_d.o \
vsip_vputlength_d.o \
vsip_vputoffset_d.o \
vsip_vputstride_d.o \
vsip_vsubview_d.o
$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
