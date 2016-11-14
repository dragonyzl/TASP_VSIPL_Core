CC=gcc
DIR=../..
INCLUDE=$(DIR)/include
LIB=$(DIR)/lib

test_fft: test_fft.c *.h
	$(CC) -o test_fft test_fft.c -g -L$(LIB) -I$(INCLUDE) -lVU_c -lvsip_c -lm

clean:
	rm test_fft
