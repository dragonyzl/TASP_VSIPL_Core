## RJudd October 11, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../../include -I../../../include/privateC
DEFINES=-DVSIP_PERFORMANCE_MODE
DEFINESD=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIB=libvsip_c.a
ARLIBD=libDvsip_c.a
ARCHIVE=../../../lib/$(ARLIB)
ARCHIVED=../../../lib/$(ARLIBD)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
COMPILED=$(CC) $(DEFINESD) $(OPTIONS)
SOURCES= vsip_valltrue_bl.c \
vsip_vand_bl.c \
vsip_vanytrue_bl.c \
vsip_vindexbool.c \
vsip_vnot_bl.c \
vsip_vor_bl.c \
vsip_vxor_bl.c \
vsip_vsumval_bl.c
OBJECTS= vsip_valltrue_bl.o \
vsip_vand_bl.o \
vsip_vanytrue_bl.o \
vsip_vindexbool.o \
vsip_vnot_bl.o \
vsip_vor_bl.o \
vsip_vxor_bl.o \
vsip_vsumval_bl.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

development:	archd

objd:	$(SOURCES)
	$(COMPILED) $(INCLUDE) -c $(SOURCES)

archd:	objd
	$(AR) $(AR_OPTIONS) $(ARCHIVED) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
