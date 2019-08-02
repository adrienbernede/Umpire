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

BUILD_DIRECTORY="build_${SYS_TYPE}_${COMPILER}"
CCONF="host-configs/${SYS_TYPE}/${COMPILER}.cmake" 

rm -rf ${BUILD_DIRECTORY} 2>/dev/null
mkdir ${BUILD_DIRECTORY} && cd ${BUILD_DIRECTORY}

cmake \
  -C ../.gitlab/conf/${CCONF} \
  -C ../${CCONF} \
  ..
cmake --build . -j 4
make test
