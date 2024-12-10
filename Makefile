CC:=cc
MPICC:=mpicc
CFLAGS:=-Wall -O3
LIBS:=-lm
STEPS:=100000000 # 100M

ifeq ($(CC),gcc)
    OMPFLAG=-fopenmp
else ifeq ($(CC),icx)
    OMPFLAG=-qopenmp
else ifeq ($(CC),clang)
    OMPFLAG=-fopenmp=libomp
endif

all: pi_seq pi_omp pi_mpi

pi_seq: pi_seq.c
	$(CC) -DSTEPS=$(STEPS) $(CFLAGS) -o $@ $< $(LIBS)

pi_omp: pi_omp.c
	$(CC) -DSTEPS=$(STEPS) $(CFLAGS) $(OMPFLAG) -o $@ $< $(LIBS)

pi_mpi: pi_mpi.c
	$(MPICC) -DSTEPS=$(STEPS) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f pi_seq pi_omp pi_mpi *.o

.PHONY: all clean

