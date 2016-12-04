all : example1t example11t example12t example13t example3t example31t 


example11t:	example11t.c
	gcc -fopenmp -o example11t example11t.c -L../../lib -I../../include -lvsip_c
example12t:	example12t.c
	gcc -fopenmp -o example12t example12t.c -L../../lib -I../../include -lvsip_c
example13t:	example13t.c
	gcc -fopenmp -o example13t example13t.c -L../../lib -I../../include -lvsip_c
example1t:	example1t.c
	gcc -fopenmp -o example1t example1t.c -L../../lib -I../../include -lvsip_c
example3t:	example3t.c
	gcc -I../../include -L../../lib -DVSIP_PERFORMANCE_MODE \
	-O2 -Wall -ansi -pedantic -fopenmp -o example3t example3t.c -lvsip_c -lm
example3t:	example31t.c
	gcc -I../../include -L../../lib -DVSIP_PERFORMANCE_MODE \
	-O2 -Wall -ansi -pedantic -fopenmp -o example31t example31t.c -lvsip_c -lm

clean:	
	rm -f example1t *.exe
	rm -f example11t *.exe
	rm -f example12t *.exe
	rm -f example13t *.exe
	rm -f example3t *.exe
	rm -f example31t *.exe
