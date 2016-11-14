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
SOURCES= vsip_cvalldestroy_d.c \
vsip_cvbind_d.c \
vsip_cvcloneview_d.c \
vsip_cvcreate_d.c \
vsip_cvdestroy_d.c \
vsip_cvget_d.c \
vsip_cvgetattrib_d.c \
vsip_cvgetblock_d.c \
vsip_cvgetoffset_d.c \
vsip_cvgetlength_d.c \
vsip_cvgetstride_d.c \
vsip_cvput_d.c \
vsip_cvputattrib_d.c \
vsip_cvputlength_d.c \
vsip_cvputoffset_d.c \
vsip_cvputstride_d.c \
vsip_cvsubview_d.c \
vsip_vimagview_d.c \
vsip_vrealview_d.c
OBJECTS= vsip_cvalldestroy_d.o \
vsip_cvbind_d.o \
vsip_cvcloneview_d.o \
vsip_cvcreate_d.o \
vsip_cvdestroy_d.o \
vsip_cvget_d.o \
vsip_cvgetattrib_d.o \
vsip_cvgetblock_d.o \
vsip_cvgetoffset_d.o \
vsip_cvgetlength_d.o \
vsip_cvgetstride_d.o \
vsip_cvput_d.o \
vsip_cvputattrib_d.o \
vsip_cvputlength_d.o \
vsip_cvputoffset_d.o \
vsip_cvputstride_d.o \
vsip_cvsubview_d.o \
vsip_vimagview_d.o \
vsip_vrealview_d.o
$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
