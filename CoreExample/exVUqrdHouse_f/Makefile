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

all:	qrdex qrdprodex

development:	qrdexD qrdprodexD

qrdprodex:	qrdprodex.c
	$(COMPILEP) qrdprodex.c -o qrdprodex $(librariesP)

qrdex:	qrdex.c VU_houseqr_f.c VU_house_f.c VU_opu_f.c VU_svmprod_f.c VU_qprodm_f.c VU_mprodq_f.c \
        VU_qtprodm_f.c VU_mprodqt_f.c VU_smvprod_f.c
	$(COMPILEP) -o qrdex qrdex.c VU_houseqr_f.c VU_house_f.c VU_mprodq_f.c VU_mprodqt_f.c \
          VU_opu_f.c VU_svmprod_f.c VU_qprodm_f.c VU_smvprod_f.c VU_qtprodm_f.c $(librariesP)

qrdexD:	qrdex.c VU_houseqr_f.c VU_house_f.c VU_opu_f.c VU_svmprod_f.c VU_qprodm_f.c VU_mprodq_f.c \
        VU_qtprodm_f.c VU_mprodqt_f.c VU_smvprod_f.c
	$(COMPILED) -o qrdex qrdex.c VU_houseqr_f.c VU_house_f.c VU_mprodq_f.c VU_mprodqt_f.c \
          VU_opu_f.c VU_svmprod_f.c VU_qprodm_f.c VU_smvprod_f.c VU_qtprodm_f.c $(librariesD)

qrdprodexD:	qrdprodex.c
	$(COMPILED) qrdprodex.c -o qrdprodex $(librariesD)

clean:
	rm -f qrdex qrdprodex
