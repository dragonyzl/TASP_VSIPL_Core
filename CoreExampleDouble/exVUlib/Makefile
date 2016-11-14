all:	tv tm tcv tcm

tv:	tv.c
	gcc -o tv tv.c -L../../lib -I../../include -lVU_c -lvsip_c

tm:	tm.c
	gcc -o tm tm.c -L../../lib -I../../include -lVU_c -lvsip_c

tcv:	tcv.c
	gcc -o tcv tcv.c -L../../lib -I../../include -lVU_c -lvsip_c

tcm:	tcm.c
	gcc -o tcm tcm.c -L../../lib -I../../include -lVU_c -lvsip_c

clean:	
	rm -f tv tm tcv tcm
