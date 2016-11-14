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
SOURCES= vsip_valldestroy_vi.c \
vsip_vbind_vi.c \
vsip_vcloneview_vi.c \
vsip_vcreate_vi.c \
vsip_vdestroy_vi.c \
vsip_vget_vi.c \
vsip_vgetattrib_vi.c \
vsip_vgetblock_vi.c \
vsip_vgetoffset_vi.c \
vsip_vgetstride_vi.c \
vsip_vgetlength_vi.c \
vsip_vput_vi.c \
vsip_vputattrib_vi.c \
vsip_vputlength_vi.c \
vsip_vputoffset_vi.c \
vsip_vputstride_vi.c \
vsip_vsubview_vi.c
OBJECTS= vsip_valldestroy_vi.o \
vsip_vbind_vi.o \
vsip_vcloneview_vi.o \
vsip_vcreate_vi.o \
vsip_vdestroy_vi.o \
vsip_vget_vi.o \
vsip_vgetattrib_vi.o \
vsip_vgetblock_vi.o \
vsip_vgetoffset_vi.o \
vsip_vgetstride_vi.o \
vsip_vgetlength_vi.o \
vsip_vput_vi.o \
vsip_vputattrib_vi.o \
vsip_vputlength_vi.o \
vsip_vputoffset_vi.o \
vsip_vputstride_vi.o \
vsip_vsubview_vi.o
$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
