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
SOURCES= vsip_malldestroy_f.c \
vsip_mbind_f.c \
vsip_mcloneview_f.c \
vsip_mcolview_f.c \
vsip_mcreate_f.c \
vsip_mdestroy_f.c \
vsip_mdiagview_f.c \
vsip_mget_f.c \
vsip_mgetattrib_f.c \
vsip_mgetblock_f.c \
vsip_mgetcollength_f.c \
vsip_mgetcolstride_f.c \
vsip_mgetoffset_f.c \
vsip_mgetrowlength_f.c \
vsip_mgetrowstride_f.c \
vsip_mput_f.c \
vsip_mputattrib_f.c \
vsip_mputcollength_f.c \
vsip_mputcolstride_f.c \
vsip_mputoffset_f.c \
vsip_mputrowlength_f.c \
vsip_mputrowstride_f.c \
vsip_mrowview_f.c \
vsip_msubview_f.c \
vsip_mtransview_f.c
OBJECTS= vsip_malldestroy_f.o \
vsip_mbind_f.o \
vsip_mcloneview_f.o \
vsip_mcolview_f.o \
vsip_mcreate_f.o \
vsip_mdestroy_f.o \
vsip_mdiagview_f.o \
vsip_mget_f.o \
vsip_mgetattrib_f.o \
vsip_mgetblock_f.o \
vsip_mgetcollength_f.o \
vsip_mgetcolstride_f.o \
vsip_mgetoffset_f.o \
vsip_mgetrowlength_f.o \
vsip_mgetrowstride_f.o \
vsip_mput_f.o \
vsip_mputattrib_f.o \
vsip_mputcollength_f.o \
vsip_mputcolstride_f.o \
vsip_mputoffset_f.o \
vsip_mputrowlength_f.o \
vsip_mputrowstride_f.o \
vsip_mrowview_f.o \
vsip_msubview_f.o \
vsip_mtransview_f.o
$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
