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
SOURCES= vsip_blockadmit_f.c \
vsip_blockbind_f.c \
vsip_blockcreate_f.c \
vsip_blockdestroy_f.c \
vsip_blockfind_f.c \
vsip_blockrebind_f.c \
vsip_blockrelease_f.c
OBJECTS= vsip_blockadmit_f.o \
vsip_blockbind_f.o \
vsip_blockcreate_f.o \
vsip_blockdestroy_f.o \
vsip_blockfind_f.o \
vsip_blockrebind_f.o \
vsip_blockrelease_f.o


$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
