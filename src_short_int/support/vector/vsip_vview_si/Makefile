## created by RJudd 
## SPAWARSYSCEN D881 
## October 11, 1998

CC=gcc
INCLUDE=-I../../../../include -I../../../../include/privateC
DEFINES=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIB=libvsip_c.a
ARCHIVE=../../../../lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES= vsip_valldestroy_si.c \
vsip_vbind_si.c \
vsip_vcloneview_si.c \
vsip_vcreate_si.c \
vsip_vdestroy_si.c \
vsip_vget_si.c \
vsip_vgetattrib_si.c \
vsip_vgetblock_si.c \
vsip_vgetlength_si.c \
vsip_vgetoffset_si.c \
vsip_vgetstride_si.c \
vsip_vput_si.c \
vsip_vputattrib_si.c \
vsip_vputlength_si.c \
vsip_vputoffset_si.c \
vsip_vputstride_si.c \
vsip_vsubview_si.c

OBJECTS= vsip_valldestroy_si.o \
vsip_vbind_si.o \
vsip_vcloneview_si.o \
vsip_vcreate_si.o \
vsip_vdestroy_si.o \
vsip_vget_si.o \
vsip_vgetattrib_si.o \
vsip_vgetblock_si.o \
vsip_vgetlength_si.o \
vsip_vgetoffset_si.o \
vsip_vgetstride_si.o \
vsip_vput_si.o \
vsip_vputattrib_si.o \
vsip_vputlength_si.o \
vsip_vputoffset_si.o \
vsip_vputstride_si.o \
vsip_vsubview_si.o

$(ARCHIVE):	$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
