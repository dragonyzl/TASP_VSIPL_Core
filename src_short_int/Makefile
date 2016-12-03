## Top Makefile for VSIP Core double
## Created by RJudd February 15, 1999
## SPAWARSYSCEN D881
## This work is the work of a government employee as part of his official duties
##
CC=gcc
INCLUDE=-I../include -I../../include/privateC
DEFINEP=-DVSIP_PERFORMANCE_MODE
DEFINED=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic -fopenmp
AR=ar
AR_OPTIONS=rcvs
ARLIBP=libvsip_c.a
ARLIBD=libDvsip_c.a
COMPILEP=$(CC) $(DEFINEP) $(OPTIONS)
COMPILED=$(CC) $(DEFINED) $(OPTIONS)
performance:
	(cd support/block/vsip_block_si; make COMPILE='$(COMPILEP)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' obj)
	(cd support/copy; make COMPILE='$(COMPILEP)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' obj)
	(cd support/vector/vsip_vview_si; make COMPILE='$(COMPILEP)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' obj)
	(cd vector/vsip_vview_si; make COMPILE='$(COMPILEP)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' obj)
	(cd vector/vsip_vview_i; make COMPILE='$(COMPILEP)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' obj)
	(cd support/block/vsip_block_si; make COMPILE='$(COMPILEP)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' arch)
	(cd support/copy; make COMPILE='$(COMPILEP)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' arch)
	(cd support/vector/vsip_vview_si; make COMPILE='$(COMPILEP)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' arch)
	(cd vector/vsip_vview_si; make COMPILE='$(COMPILEP)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' arch)
	(cd vector/vsip_vview_i; make COMPILE='$(COMPILEP)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' arch)
        

development:
	(cd support/block/vsip_block_si; make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' obj)
	(cd support/copy; make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' obj)
	(cd support/vector/vsip_vview_si; make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' obj)
	(cd vector/vsip_vview_si; make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' obj)
	(cd vector/vsip_vview_i; make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' obj)
	(cd support/block/error;   make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' obj)
	(cd support/vector/vsip_vview_si/error;  make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' obj)
	(cd support/block/vsip_block_si; make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' arch)
	(cd support/copy; make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' arch)
	(cd support/vector/vsip_vview_si; make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' arch)
	(cd vector/vsip_vview_si; make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' arch)
	(cd vector/vsip_vview_i; make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' arch)
	(cd support/block/error;   make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' arch)
	(cd support/vector/vsip_vview_si/error;  make COMPILE='$(COMPILED)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBD)' arch)
       

clean:
	(cd support/block/vsip_block_si; make clean) 
	(cd support/copy; make clean) 
	(cd support/vector/vsip_vview_si; make clean) 
	(cd vector/vsip_vview_si; make clean)
	(cd vector/vsip_vview_i; make clean)
	(cd support/block/error; make clean) 
	(cd support/vector/vsip_vview_si/error; make clean)
