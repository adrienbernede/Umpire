macro (umpire_add_executable file_name output_dir target_name)
  # Strip the suffix
  string(REGEX REPLACE "\\.[^.]*$" "" exec_name ${file_name})

  # Add executable
  blt_add_executable(
    NAME ${exec_name}
    SOURCES ${file_name}
    DEPENDS_ON umpire
    OUTPUT_DIR ${output_dir})

  list(APPEND ${target_name} ${exec_name})
endmacro ()
