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
SOURCES= vsip_cmherm_f.c \
vsip_cmprod_f.c \
vsip_cmprodh_f.c \
vsip_cmprodj_f.c \
vsip_cmprodt_f.c \
vsip_cmtrans_f.c \
vsip_cmvprod_f.c \
vsip_cvmprod_f.c \
vsip_cvouter_f.c \
vsip_cgemp_f.c \
vsip_cgems_f.c
OBJECTS= vsip_cmherm_f.o \
vsip_cmprod_f.o \
vsip_cmprodh_f.o \
vsip_cmprodj_f.o \
vsip_cmprodt_f.o \
vsip_cmtrans_f.o \
vsip_cmvprod_f.o \
vsip_cvmprod_f.o \
vsip_cvouter_f.o \
vsip_cgemp_f.o \
vsip_cgems_f.o

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
