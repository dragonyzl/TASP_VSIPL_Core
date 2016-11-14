### User Configurable Options     ###

CC          = cc
CLINKER     = $(CC)
OPTFLAGS    =  
LIB_PATH    = -L/usr/openwin/lib -lX11 -L../../lib  -lVUX_graph -lvsip_c
INCLUDE_DIR = -I../../include -I/usr/openwin/share/include
LDFLAGS     = 

### End User configurable options ###

CFLAGS  =   $(OPTFLAGS) $(INCLUDE_DIR) 
EXECS =  komegaEx

default: $(EXECS)

komegaEx :	komegaEx.o ../../include/VUX.h
	$(CLINKER) $(LDFLAGS) $(OPTFLAGS) -o komegaEx komegaEx.o \
	$(LIB_PATH) -lm

clean:
	rm -f *.o *~ $(EXECS)

.c.o:
	$(CC) $(CFLAGS) -c $*.c


