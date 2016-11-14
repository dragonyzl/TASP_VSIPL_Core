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
SOURCES= vsip_svadd_si.c \
vsip_svmul_si.c \
vsip_svsub_si.c \
vsip_vadd_si.c \
vsip_vand_si.c \
vsip_vclip_si.c \
vsip_vfill_si.c \
vsip_vgather_si.c \
vsip_vinvclip_si.c \
vsip_vleq_si.c \
vsip_vlge_si.c \
vsip_vlgt_si.c \
vsip_vlle_si.c \
vsip_vllt_si.c \
vsip_vlne_si.c \
vsip_vmag_si.c \
vsip_vmul_si.c \
vsip_vneg_si.c \
vsip_vnot_si.c \
vsip_vor_si.c \
vsip_vramp_si.c \
vsip_vscatter_si.c \
vsip_vsub_si.c \
vsip_vsumval_si.c \
vsip_vswap_si.c \
vsip_vxor_si.c
OBJECTS= vsip_svadd_si.o \
vsip_svmul_si.o \
vsip_svsub_si.o \
vsip_vadd_si.o \
vsip_vand_si.o \
vsip_vclip_si.o \
vsip_vfill_si.o \
vsip_vgather_si.o \
vsip_vinvclip_si.o \
vsip_vleq_si.o \
vsip_vlge_si.o \
vsip_vlgt_si.o \
vsip_vlle_si.o \
vsip_vllt_si.o \
vsip_vlne_si.o \
vsip_vmag_si.o \
vsip_vmul_si.o \
vsip_vneg_si.o \
vsip_vnot_si.o \
vsip_vor_si.o \
vsip_vramp_si.o \
vsip_vscatter_si.o \
vsip_vsub_si.o \
vsip_vsumval_si.o \
vsip_vswap_si.o \
vsip_vxor_si.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
