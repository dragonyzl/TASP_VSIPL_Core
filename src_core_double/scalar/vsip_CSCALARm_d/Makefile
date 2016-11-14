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
SOURCES= vsip_CADDm_d.c \
vsip_CDIVm_d.c \
vsip_CEXPm_d.c \
vsip_CJMULm_d.c \
vsip_CMPLXm_d.c \
vsip_CMULm_d.c \
vsip_CONJm_d.c \
vsip_CRDIVm_d.c \
vsip_CRECIPm_d.c \
vsip_CRSUBm_d.c \
vsip_CSQRTm_d.c \
vsip_CSUBm_d.c \
vsip_RCADDm_d.c \
vsip_RCMULm_d.c \
vsip_RCSUBm_d.c  \
vsip_CNEGm_d.c
OBJECTS= vsip_CADDm_d.o \
vsip_CDIVm_d.o \
vsip_CEXPm_d.o \
vsip_CJMULm_d.o \
vsip_CMPLXm_d.o \
vsip_CMULm_d.o \
vsip_CONJm_d.o \
vsip_CRDIVm_d.o \
vsip_CRECIPm_d.o \
vsip_CRSUBm_d.o \
vsip_CSQRTm_d.o \
vsip_CSUBm_d.o \
vsip_RCADDm_d.o \
vsip_RCMULm_d.o \
vsip_RCSUBm_d.o  \
vsip_CNEGm_d.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
