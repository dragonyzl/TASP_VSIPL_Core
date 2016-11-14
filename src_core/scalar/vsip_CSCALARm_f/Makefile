## RJudd October 11, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../../include -I../../../include/privateC
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIB=libvsip_c.a
ARCHIVE=../../../lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES= vsip_CADDm_f.c \
vsip_CDIVm_f.c \
vsip_CEXPm_f.c \
vsip_CJMULm_f.c \
vsip_CMPLXm_f.c \
vsip_CMULm_f.c \
vsip_CONJm_f.c \
vsip_CRDIVm_f.c \
vsip_CRECIPm_f.c \
vsip_CRSUBm_f.c \
vsip_CSQRTm_f.c \
vsip_CSUBm_f.c \
vsip_RCADDm_f.c \
vsip_RCMULm_f.c \
vsip_RCSUBm_f.c \
vsip_CNEGm_f.c
OBJECTS= vsip_CADDm_f.o \
vsip_CDIVm_f.o \
vsip_CEXPm_f.o \
vsip_CJMULm_f.o \
vsip_CMPLXm_f.o \
vsip_CMULm_f.o \
vsip_CONJm_f.o \
vsip_CRDIVm_f.o \
vsip_CRECIPm_f.o \
vsip_CRSUBm_f.o \
vsip_CSQRTm_f.o \
vsip_CSUBm_f.o \
vsip_RCADDm_f.o \
vsip_RCMULm_f.o \
vsip_RCSUBm_f.o \
vsip_CNEGm_f.o 

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
