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

set -e

hostname

BUILD_DIRECTORY="build_${CLUSTER}_${COMPILER}"
CCONF="host-configs/${CLUSTER}/${COMPILER}.cmake" 

if [[ "${1}" != "--test-only" ]]
then
    # If building, then delete everything first

    rm -rf ${BUILD_DIRECTORY} 2>/dev/null
    mkdir ${BUILD_DIRECTORY}
fi

# Assert that build directory exist (mainly for --test-only mode)
if [[ ! -d ${BUILD_DIRECTORY} ]]
then
    echo "Build directory not found : $(pwd)/${BUILD_DIRECTORY}"
    exit 1
fi

# Always go to build directory 
cd ${BUILD_DIRECTORY}

# Build
if [[ "${1}" != "--test-only" ]]
then
    cmake \
      -C ../.gitlab/conf/${CCONF} \
      -C ../${CCONF} \
      ..
    cmake --build . -j 4
fi

# Test
if [[ "${1}" != "--build-only" ]] 
then
    # If not building, then don’t
    ctest -T test
    tree Testing
    cp Testing/*/Test.xml ../
fi
