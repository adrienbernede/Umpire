#!/bin/bash

mkdir build_${CLUSTER}_${COMPILER}
cd build_${CLUSTER}_${COMPILER}
export CCONF=host-configs/${CLUSTER}/${COMPILER}.cmake 
cmake -C ../radiuss-ci-config/${CCONF} -C ../${CCONF} ..
srun -p pdebug -t 5 -N 1 -n 4 cmake --build -j 4 .
make test
