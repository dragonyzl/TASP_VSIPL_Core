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
SOURCES= vsip_qrd_create_f.c \
vsip_qrd_f.c  \
vsip_cqrd_create_f.c \
vsip_cqrd_f.c \
vsip_qrd_destroy_f.c \
vsip_cqrd_destroy_f.c \
vsip_qrdprodq_f.c \
vsip_cqrdprodq_f.c \
vsip_qrdsolr_f.c  \
vsip_cqrdsolr_f.c \
vsip_qrsol_f.c \
vsip_cqrsol_f.c \
vsip_qrd_getattr_f.c \
vsip_cqrd_getattr_f.c
OBJECTS= vsip_qrd_create_f.o \
vsip_qrd_f.o \
vsip_cqrd_create_f.o \
vsip_cqrd_f.o \
vsip_qrd_destroy_f.o \
vsip_cqrd_destroy_f.o \
vsip_qrdprodq_f.o \
vsip_cqrdprodq_f.o \
vsip_qrdsolr_f.o  \
vsip_cqrdsolr_f.o \
vsip_qrsol_f.o \
vsip_cqrsol_f.o \
vsip_qrd_getattr_f.o \
vsip_cqrd_getattr_f.o

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
