##############################################################################
# Copyright (c) 2018-2019, Lawrence Livermore National Security, LLC.
# Produced at the Lawrence Livermore National Laboratory
#
# Created by David Beckingsale, david@llnl.gov
# LLNL-CODE-747640
#
# All rights reserved.
#
# This file is part of Umpire.
#
# For details, see https://github.com/LLNL/Umpire
# Please also see the LICENSE file for MIT license.
##############################################################################
set (examples_dir ${UMPIRE_EXAMPLES_OUTPUT_DIR})

umpire_add_executable(malloc.cxx ${examples_dir} umpire_examples)
umpire_add_executable(strategy_example.cpp ${examples_dir} umpire_examples)

if (ENABLE_C_API)
  umpire_add_executable(allocator_c.c ${examples_dir} umpire_examples)
endif ()

umpire_add_executable(vector_allocator.cpp ${examples_dir} umpire_examples)
umpire_add_executable(size_limiter.cpp ${examples_dir} umpire_examples)

if (ENABLE_STATISTICS)
  umpire_add_executable(statistics_example.cpp ${examples_dir} umpire_examples)
endif ()

install(TARGETS
  ${umpire_examples}
  EXPORT umpire-targets
  RUNTIME DESTINATION bin/examples)

add_subdirectory(tutorial)

add_subdirectory(cookbook)
