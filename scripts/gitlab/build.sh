#!/bin/bash
##############################################################################
# Copyright (c) 2016-19, Lawrence Livermore National Security, LLC and Umpire
# project contributors. See the COPYRIGHT file for details.
#
# SPDX-License-Identifier: (MIT)
##############################################################################

set -e

BUILD_DIRECTORY="build_${SYS_TYPE}_${COMPILER}"
CCONF="host-configs/${SYS_TYPE}/${COMPILER}.cmake" 

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
    ctest -T test
    tree Testing
    cp Testing/*/Test.xml ../
fi
