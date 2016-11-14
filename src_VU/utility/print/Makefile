## RJudd October 11, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../../include
OPTIONS=-O2 -Wall -ansi -pedantic  -g
AR=ar
AR_OPTIONS=rcvs
ARLIB=libVU_c.a
ARCHIVE=../../../lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES= VU_mprintm_f.c \
VU_cmprintm_f.c \
VU_vprintm_f.c \
VU_vprintm_mi.c \
VU_vprintm_vi.c \
VU_cvprintm_f.c \
VU_mprintm_d.c \
VU_cmprintm_d.c \
VU_vprintm_d.c \
VU_cvprintm_d.c 
OBJECTS= VU_mprintm_f.o \
VU_cmprintm_f.o \
VU_vprintm_f.o \
VU_vprintm_mi.o \
VU_vprintm_vi.o \
VU_cvprintm_f.o \
VU_mprintm_d.o \
VU_cmprintm_d.o \
VU_vprintm_d.o \
VU_cvprintm_d.o 

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
