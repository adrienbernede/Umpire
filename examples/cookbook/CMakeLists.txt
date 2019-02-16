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
set (cookbook_dir ${UMPIRE_EXAMPLES_OUTPUT_DIR}/cookbook)

umpire_add_executable(recipe_no_introspection.cpp ${cookbook_dir} umpire_cookbook)

if (ENABLE_CUDA)
  umpire_add_executable(recipe_shrink.cpp ${cookbook_dir} umpire_cookbook)
  umpire_add_executable(recipe_advice_device_id.cpp ${cookbook_dir} umpire_cookbook)
  umpire_add_executable(recipe_pool_advice.cpp ${cookbook_dir} umpire_cookbook)
  umpire_add_executable(recipe_move_to_managed.cpp ${cookbook_dir} umpire_cookbook)
endif ()

umpire_add_executable(recipe_dynamic_pool_heuristic.cpp ${cookbook_dir} umpire_cookbook)

install(TARGETS
  ${umpire_cookbook}
  EXPORT umpire-targets
  RUNTIME DESTINATION bin/examples/cookbook)
