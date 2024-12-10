# Compiler settings
CC:=gcc
MPICC:=mpicc
CFLAGS:=-Wall -O3
OMPFLAGS:=-fopenmp
LIBS:=-lm
STEPS:=100000000 # 100M

# Build targets
all: pi_seq pi_omp pi_mpi

pi_seq: pi_seq.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

pi_omp: pi_omp.c
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $@ $< $(LIBS)

pi_mpi: pi_mpi.c
	$(MPICC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f pi_seq pi_omp pi_mpi *.o

.PHONY: all clean

