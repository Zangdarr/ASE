# $Id: Makefile,v 1.2 2004/10/12 09:06:17 marquet Exp $
##############################################################################

ROOTDIR=/home/enseign/ASE

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic 
CFLAGS  += -g
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES= mkhd dmps
OBJECTS	= $(addsuffix .o,\
	  mkhd dmps)

all: $(BINARIES) $(OBJECTS)


###------------------------------
### Main rules 
###------------------------------------------------------------


%.o: %.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR) $(LIBS) $(INCDIR)

mkhd: mkhd.o 
	$(CC) $(CFLAGS) -o mkhd $^ $(LIBS)

dmps: dmps.o 
	$(CC) $(CFLAGS) -o dmps $^ $(LIBS)



###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean 
	$(RM) vdiskA.bin vdiskB.bin
