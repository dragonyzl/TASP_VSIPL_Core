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
SOURCES= vsip_blockadmit_bl.c \
vsip_blockbind_bl.c \
vsip_blockcreate_bl.c \
vsip_blockdestroy_bl.c \
vsip_blockfind_bl.c \
vsip_blockrebind_bl.c \
vsip_blockrelease_bl.c
OBJECTS= vsip_blockadmit_bl.o \
vsip_blockbind_bl.o \
vsip_blockcreate_bl.o \
vsip_blockdestroy_bl.o \
vsip_blockfind_bl.o \
vsip_blockrebind_bl.o \
vsip_blockrelease_bl.o


$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
