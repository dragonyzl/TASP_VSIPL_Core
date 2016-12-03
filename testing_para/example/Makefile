all : example1 example1t example2 example2t example3 example3t

example1:	example1.c
	gcc -fopenmp -o example1 example1.c -L../../lib -I../../include -lvsip_c
example1t:	example1t.c
	gcc -fopenmp -o example1t example1t.c -L../../lib -I../../include -lvsip_c
example2:	example2.c
	gcc -I../../include -L../../lib -DVSIP_PERFORMANCE_MODE \
	-O2 -Wall -ansi -pedantic -fopenmp -o example2 example2.c -lvsip_c -lm
example2t:	example2t.c
	gcc -I../../include -L../../lib -DVSIP_PERFORMANCE_MODE \
	-O2 -Wall -ansi -pedantic -fopenmp -o example2t example2t.c -lvsip_c -lm
example3:	example3.c
	gcc -I../../include -L../../lib -DVSIP_PERFORMANCE_MODE \
	-O2 -Wall -ansi -pedantic -fopenmp -o example3 example3.c -lvsip_c -lm
example3t:	example3t.c
	gcc -I../../include -L../../lib -DVSIP_PERFORMANCE_MODE \
	-O2 -Wall -ansi -pedantic -fopenmp -o example3t example3t.c -lvsip_c -lm

clean:	
	rm -f example1 *.exe
	rm -f example1t *.exe
	rm -f example2 *.exe
	rm -f example2t *.exe
	rm -f example3 *.exe
	rm -f example3t *.exe
