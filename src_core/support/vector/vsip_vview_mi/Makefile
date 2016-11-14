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
SOURCES= vsip_valldestroy_mi.c \
vsip_vbind_mi.c \
vsip_vcloneview_mi.c \
vsip_vcreate_mi.c \
vsip_vdestroy_mi.c \
vsip_vget_mi.c \
vsip_vgetattrib_mi.c \
vsip_vgetblock_mi.c \
vsip_vgetoffset_mi.c \
vsip_vgetstride_mi.c \
vsip_vgetlength_mi.c \
vsip_vput_mi.c \
vsip_vputattrib_mi.c \
vsip_vputlength_mi.c \
vsip_vputoffset_mi.c \
vsip_vputstride_mi.c \
vsip_vsubview_mi.c
OBJECTS= vsip_valldestroy_mi.o \
vsip_vbind_mi.o \
vsip_vcloneview_mi.o \
vsip_vcreate_mi.o \
vsip_vdestroy_mi.o \
vsip_vget_mi.o \
vsip_vgetattrib_mi.o \
vsip_vgetblock_mi.o \
vsip_vgetoffset_mi.o \
vsip_vgetstride_mi.o \
vsip_vgetlength_mi.o \
vsip_vput_mi.o \
vsip_vputattrib_mi.o \
vsip_vputlength_mi.o \
vsip_vputoffset_mi.o \
vsip_vputstride_mi.o \
vsip_vsubview_mi.o
$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
