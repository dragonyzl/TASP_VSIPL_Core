CC=gcc
DIR=../..
INCLUDE=$(DIR)/include
LIB=$(DIR)/lib

test_fir: test_fir.c *.h
	$(CC) -o test_fir test_fir.c -g -L$(LIB) -I$(INCLUDE) -lVU_c -lvsip_c -lm -lefence

clean:
	rm test_fir
