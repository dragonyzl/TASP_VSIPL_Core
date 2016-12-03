## RJudd October 11, 1998 
## SPAWARSYSCEN D881 

CC=gcc
INCLUDE=-I../../../include -I../../../include/privateC
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-O2 -Wall -ansi -pedantic -fopenmp
AR=ar
AR_OPTIONS=rcvs
ARLIB=libvsip_c.a
ARCHIVE=../../../lib/$(ARLIB)
COMPILE=$(CC) $(DEFINES) $(OPTIONS)
SOURCES=vsip_crvsub_f.c \
vsip_csvadd_f.c \
vsip_csvmul_f.c \
vsip_csvsub_f.c \
vsip_cvadd_f.c \
vsip_cvam_f.c \
vsip_cvconj_f.c \
vsip_cvdiv_f.c \
vsip_cvdot_f.c \
vsip_cvexp_f.c \
vsip_cvexpoavg_f.c \
vsip_cvfill_f.c \
vsip_cvgather_f.c \
vsip_cvjdot_f.c \
vsip_cvjmul_f.c \
vsip_cvma_f.c \
vsip_cvmag_f.c \
vsip_cvmeansqval_f.c \
vsip_cvmeanval_f.c \
vsip_cvmodulate_f.c \
vsip_cvmsa_f.c \
vsip_cvmsb_f.c \
vsip_cvmul_f.c \
vsip_rvcmmul_f.c \
vsip_cvmmul_f.c \
vsip_cvneg_f.c \
vsip_cvrecip_f.c \
vsip_cvsam_f.c \
vsip_cvsbm_f.c \
vsip_cvscatter_f.c \
vsip_cvsma_f.c \
vsip_cvsmsa_f.c \
vsip_cvsqrt_f.c \
vsip_cvsub_f.c \
vsip_cvswap_f.c \
vsip_rcvadd_f.c \
vsip_rcvmul_f.c \
vsip_rcvsub_f.c \
vsip_rscvadd_f.c \
vsip_rscvmul_f.c \
vsip_rscvsub_f.c \
vsip_vcmagsq_f.c \
vsip_vcmaxmgsq_f.c \
vsip_vcmaxmgsqval_f.c \
vsip_vcminmgsq_f.c \
vsip_vcminmgsqval_f.c \
vsip_vcmplx_f.c \
vsip_veuler_f.c \
vsip_vimag_f.c \
vsip_vmodulate_f.c \
vsip_vpolar_f.c \
vsip_vreal_f.c \
vsip_vrect_f.c
OBJECTS=vsip_crvsub_f.o \
vsip_csvadd_f.o \
vsip_csvmul_f.o \
vsip_csvsub_f.o \
vsip_cvadd_f.o \
vsip_cvam_f.o \
vsip_cvconj_f.o \
vsip_cvdiv_f.o \
vsip_cvdot_f.o \
vsip_cvexp_f.o \
vsip_cvexpoavg_f.o \
vsip_cvfill_f.o \
vsip_cvgather_f.o \
vsip_cvjdot_f.o \
vsip_cvjmul_f.o \
vsip_cvma_f.o \
vsip_cvmag_f.o \
vsip_cvmeansqval_f.o \
vsip_cvmeanval_f.o \
vsip_cvmodulate_f.o \
vsip_cvmsa_f.o \
vsip_cvmsb_f.o \
vsip_cvmul_f.o \
vsip_rvcmmul_f.o \
vsip_cvmmul_f.o \
vsip_cvneg_f.o \
vsip_cvrecip_f.o \
vsip_cvsam_f.o \
vsip_cvsbm_f.o \
vsip_cvscatter_f.o \
vsip_cvsma_f.o \
vsip_cvsmsa_f.o \
vsip_cvsqrt_f.o \
vsip_cvsub_f.o \
vsip_cvswap_f.o \
vsip_rcvadd_f.o \
vsip_rcvmul_f.o \
vsip_rcvsub_f.o \
vsip_rscvadd_f.o \
vsip_rscvmul_f.o \
vsip_rscvsub_f.o \
vsip_vcmagsq_f.o \
vsip_vcmaxmgsq_f.o \
vsip_vcmaxmgsqval_f.o \
vsip_vcminmgsq_f.o \
vsip_vcminmgsqval_f.o \
vsip_vcmplx_f.o \
vsip_veuler_f.o \
vsip_vimag_f.o \
vsip_vmodulate_f.o \
vsip_vpolar_f.o \
vsip_vreal_f.o \
vsip_vrect_f.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
