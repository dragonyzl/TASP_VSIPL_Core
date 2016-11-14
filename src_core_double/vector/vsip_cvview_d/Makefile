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
SOURCES=vsip_crvsub_d.c \
vsip_csvadd_d.c \
vsip_csvmul_d.c \
vsip_csvsub_d.c \
vsip_cvadd_d.c \
vsip_cvam_d.c \
vsip_cvconj_d.c \
vsip_cvdiv_d.c \
vsip_cvdot_d.c \
vsip_cvexp_d.c \
vsip_cvexpoavg_d.c \
vsip_cvfill_d.c \
vsip_cvgather_d.c \
vsip_cvjdot_d.c \
vsip_cvjmul_d.c \
vsip_cvma_d.c \
vsip_cvmag_d.c \
vsip_cvmeansqval_d.c \
vsip_cvmeanval_d.c \
vsip_cvmodulate_d.c \
vsip_cvmsa_d.c \
vsip_cvmsb_d.c \
vsip_cvmul_d.c \
vsip_rvcmmul_d.c \
vsip_cvmmul_d.c \
vsip_cvneg_d.c \
vsip_cvrecip_d.c \
vsip_cvsam_d.c \
vsip_cvsbm_d.c \
vsip_cvscatter_d.c \
vsip_cvsma_d.c \
vsip_cvsmsa_d.c \
vsip_cvsqrt_d.c \
vsip_cvsub_d.c \
vsip_cvswap_d.c \
vsip_rcvadd_d.c \
vsip_rcvmul_d.c \
vsip_rcvsub_d.c \
vsip_rscvadd_d.c \
vsip_rscvmul_d.c \
vsip_rscvsub_d.c \
vsip_vcmagsq_d.c \
vsip_vcmaxmgsq_d.c \
vsip_vcmaxmgsqval_d.c \
vsip_vcminmgsq_d.c \
vsip_vcminmgsqval_d.c \
vsip_vcmplx_d.c \
vsip_veuler_d.c \
vsip_vimag_d.c \
vsip_vmodulate_d.c \
vsip_vpolar_d.c \
vsip_vreal_d.c \
vsip_vrect_d.c
OBJECTS=vsip_crvsub_d.o \
vsip_csvadd_d.o \
vsip_csvmul_d.o \
vsip_csvsub_d.o \
vsip_cvadd_d.o \
vsip_cvam_d.o \
vsip_cvconj_d.o \
vsip_cvdiv_d.o \
vsip_cvdot_d.o \
vsip_cvexp_d.o \
vsip_cvexpoavg_d.o \
vsip_cvfill_d.o \
vsip_cvgather_d.o \
vsip_cvjdot_d.o \
vsip_cvjmul_d.o \
vsip_cvma_d.o \
vsip_cvmag_d.o \
vsip_cvmeansqval_d.o \
vsip_cvmeanval_d.o \
vsip_cvmodulate_d.o \
vsip_cvmsa_d.o \
vsip_cvmsb_d.o \
vsip_cvmul_d.o \
vsip_rvcmmul_d.o \
vsip_cvmmul_d.o \
vsip_cvneg_d.o \
vsip_cvrecip_d.o \
vsip_cvsam_d.o \
vsip_cvsbm_d.o \
vsip_cvscatter_d.o \
vsip_cvsma_d.o \
vsip_cvsmsa_d.o \
vsip_cvsqrt_d.o \
vsip_cvsub_d.o \
vsip_cvswap_d.o \
vsip_rcvadd_d.o \
vsip_rcvmul_d.o \
vsip_rcvsub_d.o \
vsip_rscvadd_d.o \
vsip_rscvmul_d.o \
vsip_rscvsub_d.o \
vsip_vcmagsq_d.o \
vsip_vcmaxmgsq_d.o \
vsip_vcmaxmgsqval_d.o \
vsip_vcminmgsq_d.o \
vsip_vcminmgsqval_d.o \
vsip_vcmplx_d.o \
vsip_veuler_d.o \
vsip_vimag_d.o \
vsip_vmodulate_d.o \
vsip_vpolar_d.o \
vsip_vreal_d.o \
vsip_vrect_d.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
