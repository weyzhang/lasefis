lamboot -v lamhosts
mpirun -np 8 nice -19 ../bin/fdmpi ./in_and_out/fdmpi_toy.inp | tee ./in_and_out/fdmpi.out
