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
SOURCES= vsip_arg_f.c \
vsip_cadd_f.c \
vsip_cdiv_f.c \
vsip_cexp_f.c \
vsip_cjmul_f.c \
vsip_cmag_f.c \
vsip_cmagsq_f.c \
vsip_cmplx_f.c \
vsip_cmul_f.c \
vsip_cneg_f.c \
vsip_conj_f.c \
vsip_crdiv_f.c \
vsip_crecip_f.c \
vsip_crsub_f.c \
vsip_csqrt_f.c \
vsip_csub_f.c \
vsip_imag_f.c \
vsip_polar_f.c \
vsip_rcadd_f.c \
vsip_rcmul_f.c \
vsip_rcsub_f.c \
vsip_real_f.c \
vsip_rect_f.c
OBJECTS= vsip_arg_f.o \
vsip_cadd_f.o \
vsip_cdiv_f.o \
vsip_cexp_f.o \
vsip_cjmul_f.o \
vsip_cmag_f.o \
vsip_cmagsq_f.o \
vsip_cmplx_f.o \
vsip_cmul_f.o \
vsip_cneg_f.o \
vsip_conj_f.o \
vsip_crdiv_f.o \
vsip_crecip_f.o \
vsip_crsub_f.o \
vsip_csqrt_f.o \
vsip_csub_f.o \
vsip_imag_f.o \
vsip_polar_f.o \
vsip_rcadd_f.o \
vsip_rcmul_f.o \
vsip_rcsub_f.o \
vsip_real_f.o \
vsip_rect_f.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
