## RJudd February 17, 1999 
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
SOURCES= vsip_cmherm_d.c \
vsip_cmprod_d.c \
vsip_cmprodh_d.c \
vsip_cmprodj_d.c \
vsip_cmprodt_d.c \
vsip_cmtrans_d.c \
vsip_cmvprod_d.c \
vsip_cvmprod_d.c \
vsip_cvouter_d.c \
vsip_cgemp_d.c \
vsip_cgems_d.c
OBJECTS= vsip_cmherm_d.o \
vsip_cmprod_d.o \
vsip_cmprodh_d.o \
vsip_cmprodj_d.o \
vsip_cmprodt_d.o \
vsip_cmtrans_d.o \
vsip_cmvprod_d.o \
vsip_cvmprod_d.o \
vsip_cvouter_d.o \
vsip_cgemp_d.o \
vsip_cgems_d.o

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
