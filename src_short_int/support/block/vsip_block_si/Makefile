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
SOURCES= vsip_blockadmit_si.c \
vsip_blockbind_si.c \
vsip_blockcreate_si.c \
vsip_blockdestroy_si.c \
vsip_blockfind_si.c \
vsip_blockrebind_si.c \
vsip_blockrelease_si.c
OBJECTS= vsip_blockadmit_si.o \
vsip_blockbind_si.o \
vsip_blockcreate_si.o \
vsip_blockdestroy_si.o \
vsip_blockfind_si.o \
vsip_blockrebind_si.o \
vsip_blockrelease_si.o


$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
