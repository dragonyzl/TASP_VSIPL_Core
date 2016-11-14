CC=gcc
DIR=../..
INCLUDE=$(DIR)/include
LIB=$(DIR)/lib

test_sc: test_sc.c *.h
	$(CC) -o test_sc test_sc.c -g -L$(LIB) -I$(INCLUDE) -lVU_c -lvsip_c -lm

test_sc_all: test_sc_all.c *.h
	$(CC) -o test_sc_all test_sc_all.c -g -L$(LIB) -I$(INCLUDE) -lVU_c -lvsip_c -lm

atest: atest.c *.h
	$(CC) -o atest atest.c -g -L$(LIB) -I$(INCLUDE) -lVU_c -lvsip_c -lm


clean:
	rm -f atest test_sc test_sc_all
