## Modified RJudd January 9, 1998 
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
## Author: E. Robert Tisdale
##
## Revision History:
## Feb. 28, 1997	Added copyright notice.

CC=gcc
INCLUDE=-I../../include
DEFINES=-DVSIP_PERFORMANCE_MODE
DEFINESD=-DVSIP_DEVELOPMENT_MODE
OPTIONS=-O2 -Wall -ansi -pedantic
LIBRARY=-L../../lib
libraries=-lvsip_c -lm
librariesD=-lDvsip_c -lm
COMPILE=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINES) $(OPTIONS)
COMPILED=$(CC) $(INCLUDE) $(LIBRARY) $(DEFINESD) $(OPTIONS)

all: ccfftipEx ccfftopEx ccfftopExVSIP
development:	ccfftipExD ccfftopExD ccfftopExVSIPD
	

ccfftipEx:	ccfftipEx.c
	$(COMPILE) -o ccfftipEx ccfftipEx.c $(libraries)

ccfftopEx:	ccfftopEx.c
	$(COMPILE) -o ccfftopEx ccfftopEx.c $(libraries)

ccfftopExVSIP:	ccfftopExVSIP.c
	$(COMPILE) -o ccfftopExVSIP ccfftopExVSIP.c $(libraries)

ccfftipExD:	ccfftipEx.c
	$(COMPILED) -o ccfftipEx ccfftipEx.c $(librariesD)

ccfftopExD:	ccfftopEx.c
	$(COMPILED) -o ccfftopEx ccfftopEx.c $(librariesD)

ccfftopExVSIPD:	ccfftopExVSIP.c
	$(COMPILED) -o ccfftopExVSIP ccfftopExVSIP.c $(librariesD)

clean:
	rm -f ccfftipEx ccfftopEx ccfftopExVSIP *.exe
