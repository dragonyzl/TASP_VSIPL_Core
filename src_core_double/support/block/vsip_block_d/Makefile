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
SOURCES= vsip_blockadmit_d.c \
vsip_blockbind_d.c \
vsip_blockcreate_d.c \
vsip_blockdestroy_d.c \
vsip_blockfind_d.c \
vsip_blockrebind_d.c \
vsip_blockrelease_d.c
OBJECTS= vsip_blockadmit_d.o \
vsip_blockbind_d.o \
vsip_blockcreate_d.o \
vsip_blockdestroy_d.o \
vsip_blockfind_d.o \
vsip_blockrebind_d.o \
vsip_blockrelease_d.o


$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
