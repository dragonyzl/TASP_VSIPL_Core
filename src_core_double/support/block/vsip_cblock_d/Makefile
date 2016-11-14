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
SOURCES= vsip_cblockadmit_d.c \
vsip_cblockbind_d.c \
vsip_cblockcreate_d.c \
vsip_cblockdestroy_d.c \
vsip_cblockfind_d.c \
vsip_cblockrebind_d.c \
vsip_cblockrelease_d.c
OBJECTS= vsip_cblockadmit_d.o \
vsip_cblockbind_d.o \
vsip_cblockcreate_d.o \
vsip_cblockdestroy_d.o \
vsip_cblockfind_d.o \
vsip_cblockrebind_d.o \
vsip_cblockrelease_d.o


$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
