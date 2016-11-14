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
SOURCES= vsip_blockadmit_vi.c \
vsip_blockbind_vi.c \
vsip_blockcreate_vi.c \
vsip_blockdestroy_vi.c \
vsip_blockfind_vi.c \
vsip_blockrebind_vi.c \
vsip_blockrelease_vi.c
OBJECTS= vsip_blockadmit_vi.o \
vsip_blockbind_vi.o \
vsip_blockcreate_vi.o \
vsip_blockdestroy_vi.o \
vsip_blockfind_vi.o \
vsip_blockrebind_vi.o \
vsip_blockrelease_vi.o


$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
