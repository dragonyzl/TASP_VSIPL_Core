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
SOURCES=vsip_svadd_d.c \
vsip_svdiv_d.c \
vsip_svmul_d.c \
vsip_svsub_d.c \
vsip_vacos_d.c \
vsip_vadd_d.c \
vsip_vam_d.c \
vsip_vasin_d.c \
vsip_vatan2_d.c \
vsip_vatan_d.c \
vsip_vclip_d.c \
vsip_vcos_d.c \
vsip_vdiv_d.c \
vsip_vdot_d.c \
vsip_vexp10_d.c \
vsip_vexp_d.c \
vsip_vexpoavg_d.c \
vsip_vfill_d.c \
vsip_vgather_d.c \
vsip_vhypot_d.c \
vsip_vinvclip_d.c \
vsip_vleq_d.c \
vsip_vlge_d.c \
vsip_vlgt_d.c \
vsip_vlle_d.c \
vsip_vllt_d.c \
vsip_vlne_d.c \
vsip_vlog10_d.c \
vsip_vlog_d.c \
vsip_vma_d.c \
vsip_vmag_d.c \
vsip_vmax_d.c \
vsip_vmaxmg_d.c \
vsip_vmaxmgval_d.c \
vsip_vmaxval_d.c \
vsip_vmeansqval_d.c \
vsip_vmeanval_d.c \
vsip_vmin_d.c \
vsip_vminmg_d.c \
vsip_vminmgval_d.c \
vsip_vminval_d.c \
vsip_vmsa_d.c \
vsip_vmsb_d.c \
vsip_vmul_d.c \
vsip_vmmul_d.c \
vsip_vneg_d.c \
vsip_vramp_d.c \
vsip_vrecip_d.c \
vsip_vrsqrt_d.c \
vsip_vsam_d.c \
vsip_vsbm_d.c \
vsip_vscatter_d.c \
vsip_vsin_d.c \
vsip_vsma_d.c \
vsip_vsmsa_d.c \
vsip_vsq_d.c \
vsip_vsqrt_d.c \
vsip_vsub_d.c \
vsip_vsumsqval_d.c \
vsip_vsumval_d.c \
vsip_vswap_d.c \
vsip_vtan_d.c
OBJECTS= vsip_svadd_d.o \
vsip_svdiv_d.o \
vsip_svmul_d.o \
vsip_svsub_d.o \
vsip_vacos_d.o \
vsip_vadd_d.o \
vsip_vam_d.o \
vsip_vasin_d.o \
vsip_vatan2_d.o \
vsip_vatan_d.o \
vsip_vclip_d.o \
vsip_vcos_d.o \
vsip_vdiv_d.o \
vsip_vdot_d.o \
vsip_vexp10_d.o \
vsip_vexp_d.o \
vsip_vexpoavg_d.o \
vsip_vfill_d.o \
vsip_vgather_d.o \
vsip_vhypot_d.o \
vsip_vinvclip_d.o \
vsip_vleq_d.o \
vsip_vlge_d.o \
vsip_vlgt_d.o \
vsip_vlle_d.o \
vsip_vllt_d.o \
vsip_vlne_d.o \
vsip_vlog10_d.o \
vsip_vlog_d.o \
vsip_vma_d.o \
vsip_vmag_d.o \
vsip_vmax_d.o \
vsip_vmaxmg_d.o \
vsip_vmaxmgval_d.o \
vsip_vmaxval_d.o \
vsip_vmeansqval_d.o \
vsip_vmeanval_d.o \
vsip_vmin_d.o \
vsip_vminmg_d.o \
vsip_vminmgval_d.o \
vsip_vminval_d.o \
vsip_vmsa_d.o \
vsip_vmsb_d.o \
vsip_vmul_d.o \
vsip_vmmul_d.o \
vsip_vneg_d.o \
vsip_vramp_d.o \
vsip_vrecip_d.o \
vsip_vrsqrt_d.o \
vsip_vsam_d.o \
vsip_vsbm_d.o \
vsip_vscatter_d.o \
vsip_vsin_d.o \
vsip_vsma_d.o \
vsip_vsmsa_d.o \
vsip_vsq_d.o \
vsip_vsqrt_d.o \
vsip_vsub_d.o \
vsip_vsumsqval_d.o \
vsip_vsumval_d.o \
vsip_vswap_d.o \
vsip_vtan_d.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
