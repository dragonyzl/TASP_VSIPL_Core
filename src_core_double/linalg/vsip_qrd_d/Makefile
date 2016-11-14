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
SOURCES= vsip_cqrd_create_d.c \
vsip_cqrd_d.c \
vsip_cqrd_destroy_d.c \
vsip_cqrd_getattr_d.c \
vsip_cqrdprodq_d.c \
vsip_cqrdsolr_d.c \
vsip_cqrsol_d.c \
vsip_qrd_create_d.c \
vsip_qrd_d.c \
vsip_qrd_destroy_d.c \
vsip_qrd_getattr_d.c \
vsip_qrdprodq_d.c \
vsip_qrdsolr_d.c \
vsip_qrsol_d.c
OBJECTS= vsip_cqrd_create_d.o \
vsip_cqrd_d.o \
vsip_cqrd_destroy_d.o \
vsip_cqrd_getattr_d.o \
vsip_cqrdprodq_d.o \
vsip_cqrdsolr_d.o \
vsip_cqrsol_d.o \
vsip_qrd_create_d.o \
vsip_qrd_d.o \
vsip_qrd_destroy_d.o \
vsip_qrd_getattr_d.o \
vsip_qrdprodq_d.o \
vsip_qrdsolr_d.o \
vsip_qrsol_d.o

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
