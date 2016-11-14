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
SOURCES= vsip_clud_create_d.c \
vsip_clud_destroy_d.c \
vsip_clud_d.c \
vsip_clusol_d.c \
vsip_lud_create_d.c \
vsip_lud_destroy_d.c \
vsip_lud_d.c \
vsip_lusol_d.c \
vsip_lud_getattr_d.c \
vsip_clud_getattr_d.c
OBJECTS= vsip_clud_create_d.o \
vsip_clud_destroy_d.o \
vsip_clud_d.o \
vsip_clusol_d.o \
vsip_lud_create_d.o \
vsip_lud_destroy_d.o \
vsip_lud_d.o \
vsip_lusol_d.o \
vsip_lud_getattr_d.o \
vsip_clud_getattr_d.o

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
