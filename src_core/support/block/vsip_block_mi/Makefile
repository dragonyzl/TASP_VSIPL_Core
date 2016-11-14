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
SOURCES= vsip_blockadmit_mi.c \
vsip_blockbind_mi.c \
vsip_blockcreate_mi.c \
vsip_blockdestroy_mi.c \
vsip_blockfind_mi.c \
vsip_blockrebind_mi.c \
vsip_blockrelease_mi.c
OBJECTS= vsip_blockadmit_mi.o \
vsip_blockbind_mi.o \
vsip_blockcreate_mi.o \
vsip_blockdestroy_mi.o \
vsip_blockfind_mi.o \
vsip_blockrebind_mi.o \
vsip_blockrelease_mi.o


$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
