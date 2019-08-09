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

    rm -rf ${BUILD_DIRECTORY}
    mkdir ${BUILD_DIRECTORY}
fi

# Assert that build directory exist (mainly for --test-only mode)
if [[ ! -d ${BUILD_DIRECTORY} ]]
then
    echo "Build directory not found : $(pwd)/${BUILD_DIRECTORY}"
    exit 1
fi

# Always go to build directory
echo "moving to $(pwd)/${BUILD_DIRECTORY}"
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
    echo "moving to $(pwd)"
    ctest -T test
    echo "moving to $(pwd)"
    tree Testing
    cp Testing/*/Test.xml ../
fi
