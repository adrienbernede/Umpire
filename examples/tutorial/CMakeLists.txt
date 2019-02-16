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
set (tutorial_dir ${UMPIRE_EXAMPLES_OUTPUT_DIR}/tutorial)

umpire_add_executable(tut_allocator.cpp ${tutorial_dir} umpire_tutorial)

umpire_add_executable(tut_resources.cpp ${tutorial_dir} umpire_tutorial)

umpire_add_executable(tut_dynamic_pool_1.cpp ${tutorial_dir} umpire_tutorial)

umpire_add_executable(tut_dynamic_pool_2.cpp ${tutorial_dir} umpire_tutorial)

umpire_add_executable(tut_copy.cpp ${tutorial_dir} umpire_tutorial)

umpire_add_executable(tut_move.cpp ${tutorial_dir} umpire_tutorial)

umpire_add_executable(tut_memset.cpp ${tutorial_dir} umpire_tutorial)

umpire_add_executable(tut_reallocate.cpp ${tutorial_dir} umpire_tutorial)

umpire_add_executable(tut_typed_allocator.cpp ${tutorial_dir} umpire_tutorial)

umpire_add_executable(tut_introspection.cpp ${tutorial_dir} umpire_tutorial)

umpire_add_executable(tut_replay.cpp ${tutorial_dir} umpire_tutorial)

install(TARGETS
  ${umpire_tutorial}
  EXPORT umpire-targets
  RUNTIME DESTINATION bin/examples/tutorial)
