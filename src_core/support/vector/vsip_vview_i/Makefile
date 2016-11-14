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
SOURCES= vsip_valldestroy_i.c \
vsip_vbind_i.c \
vsip_vcloneview_i.c \
vsip_vcreate_i.c \
vsip_vdestroy_i.c \
vsip_vget_i.c \
vsip_vgetattrib_i.c \
vsip_vgetblock_i.c \
vsip_vgetoffset_i.c \
vsip_vgetstride_i.c \
vsip_vgetlength_i.c \
vsip_vput_i.c \
vsip_vputattrib_i.c \
vsip_vputlength_i.c \
vsip_vputoffset_i.c \
vsip_vputstride_i.c \
vsip_vsubview_i.c
OBJECTS= vsip_valldestroy_i.o \
vsip_vbind_i.o \
vsip_vcloneview_i.o \
vsip_vcreate_i.o \
vsip_vdestroy_i.o \
vsip_vget_i.o \
vsip_vgetattrib_i.o \
vsip_vgetblock_i.o \
vsip_vgetoffset_i.o \
vsip_vgetstride_i.o \
vsip_vgetlength_i.o \
vsip_vput_i.o \
vsip_vputattrib_i.o \
vsip_vputlength_i.o \
vsip_vputoffset_i.o \
vsip_vputstride_i.o \
vsip_vsubview_i.o
$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
