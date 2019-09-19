#!/bin/bash
##############################################################################
# Copyright (c) 2016-19, Lawrence Livermore National Security, LLC and Umpire
# project contributors. See the COPYRIGHT file for details.
#
# SPDX-License-Identifier: (MIT)
##############################################################################

set -e

hostname

PROJECT_DIRECTORY="$(pwd)"
BUILD_DIRECTORY="${BUILD_ROOT}/build_${SYS_TYPE}_${COMPILER}"
CCONF="host-configs/${SYS_TYPE}/${COMPILER}.cmake" 

if [[ "${1}" != "--test-only" ]]
then
    # If building, then delete everything first

    rm -rf ${BUILD_DIRECTORY}
    mkdir -p ${BUILD_DIRECTORY}
fi

# Assert that build directory exist (mainly for --test-only mode)
if [[ ! -d ${BUILD_DIRECTORY} ]]
then
    echo "Build directory not found : $(pwd)/${BUILD_DIRECTORY}"
    exit 1
fi

# Always go to build directory
echo "moving to ${BUILD_DIRECTORY}"
cd ${BUILD_DIRECTORY}

# Build
if [[ "${1}" != "--test-only" ]]
then
    cmake \
      -C ${PROJECT_DIRECTORY}/.gitlab/conf/${CCONF} \
      -C ${PROJECT_DIRECTORY}/${CCONF} \
      ${PROJECT_DIRECTORY}
    cmake --build . -j 4
fi

# Test
if [[ "${1}" != "--build-only" ]] 
then
    echo "moving to $(pwd)"
    ctest -T test
    echo "moving to $(pwd)"
    tree Testing
    . ${PYTHON_ENVIRONMENT_PATH}/bin/activate
    which python
    python ${PROJECT_DIRECTORY}/scripts/gitlab/junit/ctest2junit.py ./ ${PROJECT_DIRECTORY}/scripts/gitlab/junit/ctest2junit.xsl > test.xml
    cp test.xml ${PROJECT_DIRECTORY}
fi
