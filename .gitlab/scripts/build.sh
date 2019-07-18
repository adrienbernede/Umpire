#!/bin/bash
##############################################################################
# Copyright (c) 2018-2019, Lawrence Livermore National Security, LLC.
# Produced at the Lawrence Livermore National Laboratory
#
# Created by Adrien Bernede, bernede1@llnl.gov
# LLNL-CODE-747640
#
# All rights reserved.
#
# This file is part of Umpire.
#
# For details, see https://github.com/LLNL/Umpire
# Please also see the LICENSE file for MIT license.
##############################################################################

hostname

BUILD_SUFFIX=${CLUSTER}_${COMPILER}
CCONF=host-configs/${CLUSTER}/${COMPILER}.cmake 

rm -rf build_${BUILD_SUFFIX} 2>/dev/null
mkdir build_${BUILD_SUFFIX} && cd build_${BUILD_SUFFIX}

cmake \
  -C ../.gitlab/conf/${CCONF} \
  -C ../${CCONF} \
  ..
cmake --build -j 4 .
cmake test
