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

qrdex:	qrdex.c VU_houseqr_d.c VU_house_d.c VU_opu_d.c VU_svmprod_d.c VU_qprodm_d.c VU_mprodq_d.c \
        VU_qtprodm_d.c VU_mprodqt_d.c VU_smvprod_d.c
	$(COMPILEP) -o qrdex qrdex.c VU_houseqr_d.c VU_house_d.c VU_mprodq_d.c VU_mprodqt_d.c \
          VU_opu_d.c VU_svmprod_d.c VU_qprodm_d.c VU_smvprod_d.c VU_qtprodm_d.c $(librariesP)

qrdexD:	qrdex.c VU_houseqr_d.c VU_house_d.c VU_opu_d.c VU_svmprod_d.c VU_qprodm_d.c VU_mprodq_d.c \
        VU_qtprodm_d.c VU_mprodqt_d.c VU_smvprod_d.c
	$(COMPILED) -o qrdex qrdex.c VU_houseqr_d.c VU_house_d.c VU_mprodq_d.c VU_mprodqt_d.c \
          VU_opu_d.c VU_svmprod_d.c VU_qprodm_d.c VU_smvprod_d.c VU_qtprodm_d.c $(librariesD)

qrdprodexD:	qrdprodex.c
	$(COMPILED) qrdprodex.c -o qrdprodex $(librariesD)

clean:
	rm -f qrdex qrdprodex
