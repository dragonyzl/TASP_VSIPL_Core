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
SOURCES= vsip_blockadmit_i.c \
vsip_blockbind_i.c \
vsip_blockcreate_i.c \
vsip_blockdestroy_i.c \
vsip_blockfind_i.c \
vsip_blockrebind_i.c \
vsip_blockrelease_i.c
OBJECTS= vsip_blockadmit_i.o \
vsip_blockbind_i.o \
vsip_blockcreate_i.o \
vsip_blockdestroy_i.o \
vsip_blockfind_i.o \
vsip_blockrebind_i.o \
vsip_blockrelease_i.o


$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
