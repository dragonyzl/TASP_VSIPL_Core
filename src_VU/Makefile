## Top Makefile for VSIP Core double
## Created by RJudd February 15, 1999
## SPAWARSYSCEN D881
## This work is the work of a government employee as part of his official duties
##
CC=gcc
INCLUDE=-I../include
OPTIONS=-O2 -Wall -ansi -pedantic
AR=ar
AR_OPTIONS=rcvs
ARLIBP=libVU_c.a
COMPILE=$(CC) $(OPTIONS)
performance:
	(cd utility/print; make COMPILE='$(COMPILE)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' obj)
	(cd utility/read; make COMPILE='$(COMPILE)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' obj)
	(cd utility/print; make COMPILE='$(COMPILE)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' arch)
	(cd utility/read; make COMPILE='$(COMPILE)' AR='$(AR)' AR_OPTIONS='$(AR_OPTIONS)' ARLIB='$(ARLIBP)' arch)

clean:
	(cd utility/print; make clean) 
	(cd utility/read; make clean) 
