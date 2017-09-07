# run forward simulation to obtain observed data
QUEUE=q_x86_share
ITERATIVE=-I
NUM_PROCESS=8
bsub_job_name="ifos3d"
exec="../../bin/ifos3d"
scons -C ../../libcseife -c
scons -C ../../ -c
scons -C ../../libcseife -j8
scons -C ../../ model_scr=hh_toy_true.c -j8
#make clean
#make install  MODEL=hh_toy_true.c -j4
#mpirun -np 8 nice -19 ../bin/ifos3d ./in_and_out/ifos3d_toy_FW.json | tee ./in_and_out/ifos3D.out
submit_cmd="/usr/sw-mpp/bin/bsub  $ITERATIVE -q  $QUEUE \
-n $NUM_PROCESS -o bsub.out -J $bsub_job_name"
CMD="$submit_cmd $exec
    ./in_and_out/ifos3d_toy_FW.json | tee ./in_and_out/ifos3D.out
    "
eval $CMD

cp model/toy.vs_it0 model/toy.vs.true
cp model/toy.vp_it0 model/toy.vp.true
cp model/toy.rho_it0 model/toy.rho.true


# invert observed data using homogeneous starting model
scons -C ../../libcseife -c
scons -C ../../ -c
scons -C ../../libcseife -j8
scons -C ../../ model_scr=hh_toy_true.c -j8
#make clean 
#make install MODEL=hh_toy_start.c -j4
# mpirun -np 8 nice -19 ../bin/ifos3d ./in_and_out/ifos3d_toy.json | tee ./in_and_out/ifos3D_INV.out
submit_cmd="/usr/sw-mpp/bin/bsub  $ITERATIVE -q  $QUEUE \
-n $NUM_PROCESS -o bsub.out -J $bsub_job_name"
CMD="$submit_cmd $exec
    ./in_and_out/ifos3d_toy.json | tee ./in_and_out/ifos3D_INV.out
    "
eval $CMD
