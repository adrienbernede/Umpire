#!/bin/bash
##############################################################################
# Copyright (c) 2016-19, Lawrence Livermore National Security, LLC and Umpire
# project contributors. See the COPYRIGHT file for details.
#
# SPDX-License-Identifier: (MIT)
##############################################################################

set -e

PROJECT_DIRECTORY="$(pwd)"
BUILD_DIRECTORY="${BUILD_ROOT}/build_${SYS_TYPE}_${COMPILER}"

. ${PYTHON_ENVIRONMENT_PATH}/bin/activate

echo "moving to ${BUILD_DIRECTORY}"
cd ${BUILD_DIRECTORY}

python ${PROJECT_DIRECTORY}/scripts/gitlab/junit/ctest2junit.py ./ ${PROJECT_DIRECTORY}/scripts/gitlab/junit/ctest2junit.xsl > test.xml

cp test.xml ${PROJECT_DIRECTORY}/
