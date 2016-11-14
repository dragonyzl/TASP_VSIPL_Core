CC=gcc
INCLUDE=-I../../include
DEFINEP=-DVSIP_PERFORMANCE_MODE
DEFINED=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic 
LIBRARY=-L../../lib
librariesP=-lVU_c -lvsip_c -lm
librariesD=-lVU_c -lDvsip_c -lm
COMPILEP=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINEP) $(OPTIONS)
COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINED) $(OPTIONS)

cqrdex:	cqrdex.c VU_chouseqr_f.c VU_chouse_f.c VU_copu_f.c VU_copuh_f.c \
        VU_rscjvmprod_f.c VU_cqprodm_f.c VU_cmprodq_f.c  VU_cqhprodm_f.c \
        VU_cmprodqh_f.c VU_rscvmprod_f.c VU_rscjmvprod_f.c VU_rscmvprod_f.c 
	$(COMPILEP) -o cqrdex cqrdex.c VU_chouseqr_f.c VU_chouse_f.c VU_cmprodq_f.c \
        VU_cmprodqh_f.c VU_rscvmprod_f.c VU_copu_f.c VU_chopu_f.c VU_copuh_f.c \
        VU_rscjvmprod_f.c VU_cqprodm_f.c VU_rscjmvprod_f.c VU_rscmvprod_f.c \
        VU_cqhprodm_f.c $(librariesP)

clean:
	rm -f cqrdex
