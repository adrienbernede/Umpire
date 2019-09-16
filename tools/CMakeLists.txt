##############################################################################
# Copyright (c) 2016-19, Lawrence Livermore National Security, LLC and Umpire
# project contributors. See the COPYRIGHT file for details.
#
# SPDX-License-Identifier: (MIT)
##############################################################################

set(tools_depends umpire)

if (ENABLE_HIP)
  set(tools_depends ${tools_depends} hip_runtime)
endif()

set(replay_headers
  replay/ReplayInterpreter.hpp
  replay/ReplayInterpreter.inl
  replay/ReplayMacros.hpp
  replay/ReplayOperationManager.hpp
  replay/ReplayOperationManager.inl)

set(replay_sources
  replay/ReplayInterpreter.cpp
  replay/ReplayOperationManager.cpp)

blt_add_executable(
  NAME replay
  SOURCES replay/replay.cpp ${replay_sources}
  INCLUDES ${PROJECT_SOURCE_DIR}/tools
  DEPENDS_ON ${tools_depends}
  OUTPUT_DIR ${TOOL_OUTPUT_DIRECTORY})
list(APPEND umpire_tools replay)

target_include_directories(replay
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/tools>)

blt_add_executable(
  NAME replaydiff
  SOURCES replay/replaydiff.cpp ${replay_sources}
  INCLUDES ${PROJECT_SOURCE_DIR}/tools
  DEPENDS_ON ${tools_depends}
  OUTPUT_DIR ${TOOL_OUTPUT_DIRECTORY})
list(APPEND umpire_tools replaydiff)

target_include_directories(replaydiff
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/tools>)

install(
  FILES analysis/plot_allocations analysis/plot_allocator_traces
  DESTINATION ${UMPIRE_TOOL_INSTALL_DIRECTORY})

install(TARGETS ${umpire_tools} DESTINATION ${UMPIRE_TOOL_INSTALL_DIRECTORY})
