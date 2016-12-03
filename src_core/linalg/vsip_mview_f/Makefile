## RJudd October 11, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../../include -I../../../include/privateC
DEFINES=-DVSIP_PERFORMANCE_MODE
DEFINESD=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic -fopenmp
AR=ar
AR_OPTIONS=rcvs
ARLIB=libvsip_c.a
ARLIBD=libDvsip_c.a
ARCHIVE=../../../lib/$(ARLIB)
ARCHIVED=../../../lib/$(ARLIBD)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
COMPILED=$(CC) $(DEFINESD) $(OPTIONS)
SOURCES= vsip_mprod_f.c \
vsip_mprodt_f.c \
vsip_mtrans_f.c \
vsip_mvprod_f.c \
vsip_vmprod_f.c \
vsip_vouter_f.c \
vsip_gemp_f.c \
vsip_gemp_f_para.c \
vsip_gems_f_para.c \
vsip_gems_f.c
OBJECTS= vsip_mprod_f.o \
vsip_mprodt_f.o \
vsip_mtrans_f.o \
vsip_mvprod_f.o \
vsip_vmprod_f.o \
vsip_vouter_f.o \
vsip_gemp_f.o \
vsip_gemp_f_para.o \
vsip_gems_f_para.o \
vsip_gems_f.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

SOURCES_PARA= vsip_gemp_f_para.c \
vsip_gems_f_para.c
OBJECTS_PARA= vsip_gemp_f_para.o \
vsip_gems_f_para.o

ARCHIVE_PARA=../../../lib/$(ARLIB)
$(ARCHIVE_PARA):		$(OBJECTS_PARA)
	$(AR) $(AR_OPTIONS) $(ARCHIVE_PARA) $(OBJECTS_PARA)

para:	arch_para

$(OBJECTS_PARA):	$(SOURCES_PARA)
	$(COMPILE) $(INCLUDE) -c $(SOURCES_PARA)

obj_para:	$(OBJECTS_PARA)

arch_para:
	$(AR) $(AR_OPTIONS) $(ARCHIVE_PARA) $(OBJECTS_PARA)

paraclean:
	rm -f $(OBJECTS_PARA)


development:	archd

objd:	$(SOURCES)
	$(COMPILED) $(INCLUDE) -c $(SOURCES)

archd:	objd
	$(AR) $(AR_OPTIONS) $(ARCHIVED) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
