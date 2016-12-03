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
SOURCES=vsip_svadd_f.c \
vsip_svdiv_f.c \
vsip_svmul_f.c \
vsip_svsub_f.c \
vsip_vacos_f.c \
vsip_vadd_f.c \
vsip_vam_f.c \
vsip_vasin_f.c \
vsip_vatan2_f.c \
vsip_vatan_f.c \
vsip_vclip_f.c \
vsip_vcos_f.c \
vsip_vdiv_f.c \
vsip_vdot_f.c \
vsip_vdot_f_para.c \
vsip_vexp10_f.c \
vsip_vexp_f.c \
vsip_vexpoavg_f.c \
vsip_vfill_f.c \
vsip_vgather_f.c \
vsip_vhypot_f.c \
vsip_vinvclip_f.c \
vsip_vleq_f.c \
vsip_vlge_f.c \
vsip_vlgt_f.c \
vsip_vlle_f.c \
vsip_vllt_f.c \
vsip_vlne_f.c \
vsip_vlog10_f.c \
vsip_vlog_f.c \
vsip_vma_f.c \
vsip_vmag_f.c \
vsip_vmax_f.c \
vsip_vmaxmg_f.c \
vsip_vmaxmgval_f.c \
vsip_vmaxval_f.c \
vsip_vmeansqval_f.c \
vsip_vmeanval_f.c \
vsip_vmin_f.c \
vsip_vminmg_f.c \
vsip_vminmgval_f.c \
vsip_vminval_f.c \
vsip_vmsa_f.c \
vsip_vmsb_f.c \
vsip_vmul_f.c \
vsip_vmul_f_para.c \
vsip_vmmul_f.c \
vsip_vneg_f.c \
vsip_vramp_f.c \
vsip_vrecip_f.c \
vsip_vrsqrt_f.c \
vsip_vsam_f.c \
vsip_vsbm_f.c \
vsip_vscatter_f.c \
vsip_vsin_f.c \
vsip_vsma_f.c \
vsip_vsmsa_f.c \
vsip_vsq_f.c \
vsip_vsqrt_f.c \
vsip_vsub_f.c \
vsip_vsumsqval_f.c \
vsip_vsumsqval_f_para.c \
vsip_vsumval_f.c \
vsip_vsumval_f_para.c \
vsip_vswap_f.c \
vsip_vtan_f.c

OBJECTS= vsip_svadd_f.o \
vsip_svdiv_f.o \
vsip_svmul_f.o \
vsip_svsub_f.o \
vsip_vacos_f.o \
vsip_vadd_f.o \
vsip_vam_f.o \
vsip_vasin_f.o \
vsip_vatan2_f.o \
vsip_vatan_f.o \
vsip_vclip_f.o \
vsip_vcos_f.o \
vsip_vdiv_f.o \
vsip_vdot_f.o \
vsip_vdot_f_para.o \
vsip_vexp10_f.o \
vsip_vexp_f.o \
vsip_vexpoavg_f.o \
vsip_vfill_f.o \
vsip_vgather_f.o \
vsip_vhypot_f.o \
vsip_vinvclip_f.o \
vsip_vleq_f.o \
vsip_vlge_f.o \
vsip_vlgt_f.o \
vsip_vlle_f.o \
vsip_vllt_f.o \
vsip_vlne_f.o \
vsip_vlog10_f.o \
vsip_vlog_f.o \
vsip_vma_f.o \
vsip_vmag_f.o \
vsip_vmax_f.o \
vsip_vmaxmg_f.o \
vsip_vmaxmgval_f.o \
vsip_vmaxval_f.o \
vsip_vmeansqval_f.o \
vsip_vmeanval_f.o \
vsip_vmin_f.o \
vsip_vminmg_f.o \
vsip_vminmgval_f.o \
vsip_vminval_f.o \
vsip_vmsa_f.o \
vsip_vmsb_f.o \
vsip_vmul_f.o \
vsip_vmul_f_para.o \
vsip_vmmul_f.o \
vsip_vneg_f.o \
vsip_vramp_f.o \
vsip_vrecip_f.o \
vsip_vrsqrt_f.o \
vsip_vsam_f.o \
vsip_vsbm_f.o \
vsip_vscatter_f.o \
vsip_vsin_f.o \
vsip_vsma_f.o \
vsip_vsmsa_f.o \
vsip_vsq_f.o \
vsip_vsqrt_f.o \
vsip_vsub_f.o \
vsip_vsumsqval_f.o \
vsip_vsumsqval_f_para.o \
vsip_vsumval_f.o \
vsip_vsumval_f_para.o \
vsip_vswap_f.o \
vsip_vtan_f.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)


obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)


SOURCES_PARA= vsip_vsumsqval_f_para.c \
vsip_vsumval_f_para.c \
vsip_vdot_f_para.c \
vsip_vmul_f_para.c
OBJECTS_PARA= vsip_vsumsqval_f_para.o \
vsip_vsumval_f_para.o \
vsip_vdot_f_para.o \
vsip_vmul_f_para.o

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


clean:
	rm -f $(OBJECTS)

