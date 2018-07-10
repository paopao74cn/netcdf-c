SET(abs_top_srcdir ${CMAKE_CURRENT_SOURCE_DIR})

remove_definitions(-DDLL_EXPORT)

FILE(GLOB COPY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.sh)

FILE(COPY ${COPY_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ FILE_PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE)

IF(ENABLE_TESTS)

  # Base tests
  # The tests are set up as a combination of shell scripts and executables that
  # must be run in a particular order. It is painful but will use macros to help
  # keep it from being too bad.

  IF(BUILD_UTILITIES)
#    add_sh_test(dap4_test test_raw)
  ENDIF(BUILD_UTILITIES)

ENDIF(ENABLE_TESTS)

## Specify files to be distributed by 'make dist'
FILE(GLOB CUR_EXTRA_DIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.c ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.sh
)
SET(CUR_EXTRA_DIST ${CUR_EXTRA_DIST} CMakeLists.txt Makefile.am)
ADD_EXTRA_DIST("${CUR_EXTRA_DIST}")
