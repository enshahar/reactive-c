project (reactive)
cmake_minimum_required(VERSION 2.4)

SET(LIBS "reactive-c/reactive.c" "unit/test.c" "unknown/unknown.c")

# top-level target, run-targets for each executable are added below
add_custom_target(run)

SET(ALL_EXECUTABLES)
macro(add_executable name)
  _add_executable(${ARGV})
  # create a run_<executable> target for each executable
  add_custom_target(run_${name}
    DEPENDS ${name}
    COMMENT "Running ${name}..."
    COMMAND ${name}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
  )
  # and make it a dependency of the generic run target
  add_dependencies(run "run_${name}")
endmacro()

# create executables of all example files in the current directory
file(GLOB EXAMPLES *.c)
foreach(example ${EXAMPLES})
  message(STATUS "Adding example ${example}")
  get_filename_component(name ${example} NAME_WE)
  add_executable(${name} ${example} ${LIBS})
endforeach()