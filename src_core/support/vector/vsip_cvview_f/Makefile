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
SOURCES= vsip_cvalldestroy_f.c \
vsip_cvbind_f.c \
vsip_cvcloneview_f.c \
vsip_cvcreate_f.c \
vsip_cvdestroy_f.c \
vsip_cvget_f.c \
vsip_cvgetattrib_f.c \
vsip_cvgetblock_f.c \
vsip_cvgetoffset_f.c \
vsip_cvgetlength_f.c \
vsip_cvgetstride_f.c \
vsip_cvput_f.c \
vsip_cvputattrib_f.c \
vsip_cvputlength_f.c \
vsip_cvputoffset_f.c \
vsip_cvputstride_f.c \
vsip_cvsubview_f.c \
vsip_vimagview_f.c \
vsip_vrealview_f.c
OBJECTS= vsip_cvalldestroy_f.o \
vsip_cvbind_f.o \
vsip_cvcloneview_f.o \
vsip_cvcreate_f.o \
vsip_cvdestroy_f.o \
vsip_cvget_f.o \
vsip_cvgetattrib_f.o \
vsip_cvgetblock_f.o \
vsip_cvgetoffset_f.o \
vsip_cvgetlength_f.o \
vsip_cvgetstride_f.o \
vsip_cvput_f.o \
vsip_cvputattrib_f.o \
vsip_cvputlength_f.o \
vsip_cvputoffset_f.o \
vsip_cvputstride_f.o \
vsip_cvsubview_f.o \
vsip_vimagview_f.o \
vsip_vrealview_f.o
$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
