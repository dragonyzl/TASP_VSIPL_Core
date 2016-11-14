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
SOURCES= vsip_valldestroy_f.c \
vsip_vbind_f.c \
vsip_vcloneview_f.c \
vsip_vcreate_f.c \
vsip_vdestroy_f.c \
vsip_vget_f.c \
vsip_vgetattrib_f.c \
vsip_vgetblock_f.c \
vsip_vgetoffset_f.c \
vsip_vgetstride_f.c \
vsip_vgetlength_f.c \
vsip_vput_f.c \
vsip_vputattrib_f.c \
vsip_vputlength_f.c \
vsip_vputoffset_f.c \
vsip_vputstride_f.c \
vsip_vsubview_f.c
OBJECTS= vsip_valldestroy_f.o \
vsip_vbind_f.o \
vsip_vcloneview_f.o \
vsip_vcreate_f.o \
vsip_vdestroy_f.o \
vsip_vget_f.o \
vsip_vgetattrib_f.o \
vsip_vgetblock_f.o \
vsip_vgetoffset_f.o \
vsip_vgetstride_f.o \
vsip_vgetlength_f.o \
vsip_vput_f.o \
vsip_vputattrib_f.o \
vsip_vputlength_f.o \
vsip_vputoffset_f.o \
vsip_vputstride_f.o \
vsip_vsubview_f.o
$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
