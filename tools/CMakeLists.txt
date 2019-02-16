##############################################################################
# Copyright (c) 2018, Lawrence Livermore National Security, LLC.
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
set (tools_dir ${CMAKE_BINARY_DIR}/tools)

umpire_add_executable(replay.cpp ${tools_dir} umpire_tools)

umpire_add_executable(replay_allocation_map.cpp ${tools_dir} umpire_tools)

install(TARGETS
  ${umpire_tools}
  EXPORT umpire-targets
  RUNTIME DESTINATION bin/tools)
