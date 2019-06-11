if(ENABLE_TESTS)
    set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full --gen-suppressions=all --show-leak-kinds=all")
    file(TO_CMAKE_PATH "${CMAKE_SOURCE_DIR}/cmake/valgrind.supp" MEMORYCHECK_SUPPRESSIONS_FILE)
    include(CTest)
    message(STATUS "Memcheck suppressions file: ${MEMORYCHECK_SUPPRESSIONS_FILE}")
endif()