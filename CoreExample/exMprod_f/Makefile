## Modified RJudd Feruary 24, 1998
## SPAWARSYSCEN D881 
## Makefile Version 0.000 February 28, 1997
## 
## This file contains rules for making the VSIP eaxmple program.
##
## Copyright Hughes Research Laboratories, Inc.  A non-exclusive, non-royalty 
## bearing license is hereby granted to all persons to copy, modify, distribute 
## and produce derivative works for any purpose, provided that this copyright 
## notice and following disclaimer appear on all copies.  THIS LICENSE INCLUDES 
## NO WARRANTEES, EXPRESSED OR IMPLIED, WHETHER ORAL OR WRITTEN, WITH RESPECT TO
## THE SOFTWARE OR OTHER MATERIAL, INCLUDING BUT NOT LIMITED TO ANY IMPLIED
## WARRANTIES OF MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE, OR
## ARISING FROM A COURSE OF PERFORMANCE, OR DEALING, OR FROM USAGE OR TRADE,
## OR OF NON-INFRINGEMENT OF ANY PATENTS OF THIRD PARTIES.
##
## This material is based upon work supported by Ft. Uuachuca/DARPA under
## Contract No.  DABT63-96-C-0060.  Any opinions, findings and conclusions
## or recommendations expressed in this material are those of the author(s)
## and do not necessarily reflect the views of Ft. Huachuca/DARPA.
##

CC=gcc
INCLUDE=-I../../include 
DEFINES=-DVSIP_PERFORMANCE_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
LIBRARY=-L../../lib
libraries=-lvsip_c \
           -lm
COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)

all: mvprodEx vmprodEx cmprodhEx cmprodtEx mprodtEx cmprodjEx cmprodEx mprodEx \
     cvmprodEx cmvprodEx
	
cmvprodEx:	cmvprodEx.c
	$(COMPILE) -o cmvprodEx cmvprodEx.c $(libraries)

cvmprodEx:	cvmprodEx.c
	$(COMPILE) -o cvmprodEx cvmprodEx.c $(libraries)

vmprodEx:	vmprodEx.c
	$(COMPILE) -o vmprodEx vmprodEx.c $(libraries)

mvprodEx:	mvprodEx.c
	$(COMPILE) -o mvprodEx mvprodEx.c $(libraries)

mprodEx:	mprodEx.c
	$(COMPILE) -o mprodEx mprodEx.c $(libraries)

cmprodEx:	cmprodEx.c
	$(COMPILE) -o cmprodEx cmprodEx.c $(libraries)

cmprodtEx:	cmprodtEx.c
	$(COMPILE) -o cmprodtEx cmprodtEx.c $(libraries)

cmprodjEx:	cmprodjEx.c
	$(COMPILE) -o cmprodjEx cmprodjEx.c $(libraries)

cmprodhEx:	cmprodhEx.c
	$(COMPILE) -o cmprodhEx cmprodhEx.c $(libraries)

mprodtEx:	mprodtEx.c
	$(COMPILE) -o mprodtEx mprodtEx.c $(libraries)

clean:
	rm -f cmprodhEx  mprodtEx cmprodtEx  cmprodjEx cmprodEx mprodEx \
              mvprodEx vmprodEx cvmprodEx cmvprodEx *.exe
