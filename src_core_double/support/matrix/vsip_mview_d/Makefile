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
SOURCES= vsip_malldestroy_d.c \
vsip_mbind_d.c \
vsip_mcloneview_d.c \
vsip_mcolview_d.c \
vsip_mcreate_d.c \
vsip_mdestroy_d.c \
vsip_mdiagview_d.c \
vsip_mget_d.c \
vsip_mgetattrib_d.c \
vsip_mgetblock_d.c \
vsip_mgetcollength_d.c \
vsip_mgetcolstride_d.c \
vsip_mgetoffset_d.c \
vsip_mgetrowlength_d.c \
vsip_mgetrowstride_d.c \
vsip_mput_d.c \
vsip_mputattrib_d.c \
vsip_mputcollength_d.c \
vsip_mputcolstride_d.c \
vsip_mputoffset_d.c \
vsip_mputrowlength_d.c \
vsip_mputrowstride_d.c \
vsip_mrowview_d.c \
vsip_msubview_d.c \
vsip_mtransview_d.c
OBJECTS= vsip_malldestroy_d.o \
vsip_mbind_d.o \
vsip_mcloneview_d.o \
vsip_mcolview_d.o \
vsip_mcreate_d.o \
vsip_mdestroy_d.o \
vsip_mdiagview_d.o \
vsip_mget_d.o \
vsip_mgetattrib_d.o \
vsip_mgetblock_d.o \
vsip_mgetcollength_d.o \
vsip_mgetcolstride_d.o \
vsip_mgetoffset_d.o \
vsip_mgetrowlength_d.o \
vsip_mgetrowstride_d.o \
vsip_mput_d.o \
vsip_mputattrib_d.o \
vsip_mputcollength_d.o \
vsip_mputcolstride_d.o \
vsip_mputoffset_d.o \
vsip_mputrowlength_d.o \
vsip_mputrowstride_d.o \
vsip_mrowview_d.o \
vsip_msubview_d.o \
vsip_mtransview_d.o
$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
