## RJudd October 11, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../../../include -I../../../../include/privateC
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIB=libDvsip_c.a
ARCHIVE=../../../../lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES= vsip_blockcheck_markings.c \
vsip_blockcheck_valid_f.c \
vsip_blockcheck_valid_i.c \
vsip_cblockcheck_markings.c \
vsip_cblockcheck_valid_f.c \
vsip_blockcheck_valid_bl.c \
vsip_blockcheck_valid_vi.c
OBJECTS= vsip_blockcheck_markings.o \
vsip_blockcheck_valid_f.o \
vsip_blockcheck_valid_i.o \
vsip_cblockcheck_markings.o \
vsip_cblockcheck_valid_f.o \
vsip_blockcheck_valid_bl.o \
vsip_blockcheck_valid_vi.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
