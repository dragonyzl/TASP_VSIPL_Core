## Created RJudd February 16, 1999
## SPWARSYSCNE D881 

all: 	vmmulEx rvcmmulEx cvmmulEx
	

vmmulEx :	vmmulEx.c
	gcc -o vmmulEx vmmulEx.c -L../../lib -I../../include -lVU_c -lvsip_c

rvcmmulEx :	rvcmmulEx.c
	gcc -o rvcmmulEx rvcmmulEx.c -L../../lib -I../../include -lVU_c -lvsip_c

cvmmulEx :	cvmmulEx.c
	gcc -o cvmmulEx cvmmulEx.c -L../../lib -I../../include -lVU_c -lvsip_c

clean:	
	 rm -f vmmulEx rvcmmulEx cvmmulEx 
