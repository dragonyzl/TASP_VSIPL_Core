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
SOURCES= vsip_arg_d.c \
vsip_cadd_d.c \
vsip_cdiv_d.c \
vsip_cexp_d.c \
vsip_cjmul_d.c \
vsip_cmag_d.c \
vsip_cmagsq_d.c \
vsip_cmplx_d.c \
vsip_cmul_d.c \
vsip_cneg_d.c \
vsip_conj_d.c \
vsip_crdiv_d.c \
vsip_crecip_d.c \
vsip_crsub_d.c \
vsip_csqrt_d.c \
vsip_csub_d.c \
vsip_imag_d.c \
vsip_polar_d.c \
vsip_rcadd_d.c \
vsip_rcmul_d.c \
vsip_rcsub_d.c \
vsip_real_d.c \
vsip_rect_d.c
OBJECTS= vsip_arg_d.o \
vsip_cadd_d.o \
vsip_cdiv_d.o \
vsip_cexp_d.o \
vsip_cjmul_d.o \
vsip_cmag_d.o \
vsip_cmagsq_d.o \
vsip_cmplx_d.o \
vsip_cmul_d.o \
vsip_cneg_d.o \
vsip_conj_d.o \
vsip_crdiv_d.o \
vsip_crecip_d.o \
vsip_crsub_d.o \
vsip_csqrt_d.o \
vsip_csub_d.o \
vsip_imag_d.o \
vsip_polar_d.o \
vsip_rcadd_d.o \
vsip_rcmul_d.o \
vsip_rcsub_d.o \
vsip_real_d.o \
vsip_rect_d.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
