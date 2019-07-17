#!/bin/bash

hostname

mkdir build_${CLUSTER}_${COMPILER}
cd build_${CLUSTER}_${COMPILER}

export CCONF=host-configs/${CLUSTER}/${COMPILER}.cmake 

cmake -C ../radiuss-ci-config/${CCONF} -C ../${CCONF} ..
cmake --build -j 4 .
make test
