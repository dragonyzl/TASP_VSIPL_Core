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
SOURCES= vsip_cblockadmit_f.c \
vsip_cblockbind_f.c \
vsip_cblockcreate_f.c \
vsip_cblockdestroy_f.c \
vsip_cblockfind_f.c \
vsip_cblockrebind_f.c \
vsip_cblockrelease_f.c \
vsip_cstorage.c
OBJECTS= vsip_cblockadmit_f.o \
vsip_cblockbind_f.o \
vsip_cblockcreate_f.o \
vsip_cblockdestroy_f.o \
vsip_cblockfind_f.o \
vsip_cblockrebind_f.o \
vsip_cblockrelease_f.o \
vsip_cstorage.o


$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
