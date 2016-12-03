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
SOURCES=vsip_svadd_i.c \
vsip_svsub_i.c \
vsip_vadd_i.c \
vsip_vand_i.c \
vsip_vclip_i.c \
vsip_vfill_i.c \
vsip_vgather_i.c \
vsip_vinvclip_i.c \
vsip_vmul_i.c \
vsip_vneg_i.c \
vsip_vnot_i.c \
vsip_vor_i.c \
vsip_vramp_i.c \
vsip_vscatter_i.c \
vsip_vsub_i.c \
vsip_vsumval_i.c \
vsip_vswap_i.c \
vsip_vxor_i.c \
vsip_svmul_i.c \
vsip_vmag_i.c 
OBJECTS=vsip_svadd_i.o \
vsip_svsub_i.o \
vsip_vadd_i.o \
vsip_vand_i.o \
vsip_vclip_i.o \
vsip_vfill_i.o \
vsip_vgather_i.o \
vsip_vinvclip_i.o \
vsip_vmul_i.o \
vsip_vneg_i.o \
vsip_vnot_i.o \
vsip_vor_i.o \
vsip_vramp_i.o \
vsip_vscatter_i.o \
vsip_vsub_i.o \
vsip_vsumval_i.o \
vsip_vswap_i.o \
vsip_vxor_i.o \
vsip_svmul_i.o \
vsip_vmag_i.o

$(ARCHIVE):		$(OBJECTS)
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

$(OBJECTS):	$(SOURCES)
	$(COMPILE) $(INCLUDE) -c $(SOURCES)

obj:	$(OBJECTS)

arch:
	$(AR) $(AR_OPTIONS) $(ARCHIVE) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
