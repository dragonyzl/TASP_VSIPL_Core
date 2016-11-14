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
SOURCES= vsip_valldestroy_bl.c \
vsip_vbind_bl.c \
vsip_vcloneview_bl.c \
vsip_vcreate_bl.c \
vsip_vdestroy_bl.c \
vsip_vget_bl.c \
vsip_vgetattrib_bl.c \
vsip_vgetblock_bl.c \
vsip_vgetoffset_bl.c \
vsip_vgetstride_bl.c \
vsip_vgetlength_bl.c \
vsip_vput_bl.c \
vsip_vputattrib_bl.c \
vsip_vputlength_bl.c \
vsip_vputoffset_bl.c \
vsip_vputstride_bl.c \
vsip_vsubview_bl.c
OBJECTS= vsip_valldestroy_bl.o \
vsip_vbind_bl.o \
vsip_vcloneview_bl.o \
vsip_vcreate_bl.o \
vsip_vdestroy_bl.o \
vsip_vget_bl.o \
vsip_vgetattrib_bl.o \
vsip_vgetblock_bl.o \
vsip_vgetoffset_bl.o \
vsip_vgetstride_bl.o \
vsip_vgetlength_bl.o \
vsip_vput_bl.o \
vsip_vputattrib_bl.o \
vsip_vputlength_bl.o \
vsip_vputoffset_bl.o \
vsip_vputstride_bl.o \
vsip_vsubview_bl.o
$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
