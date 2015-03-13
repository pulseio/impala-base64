cmake_minimum_required(VERSION 2.6)

# where to put generated libraries
set(LIBRARY_OUTPUT_PATH "build")
# where to put generated binaries
set(EXECUTABLE_OUTPUT_PATH "build")

find_package(Git)

if(GIT_FOUND)
  execute_process(COMMAND ${GIT_EXECUTABLE} describe --dirty OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE GIT_TAG)
  if(GIT_TAG)
    set(GIT_TAG "-${GIT_TAG}")
  endif(GIT_TAG)
endif(GIT_FOUND)

set(UDF_LIBRARY PulseB64Udf${GIT_TAG})

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -std=c++11")

# Build the UDA/UDFs into a shared library.
add_library(${UDF_LIBRARY} SHARED base64.cc base64-encode-udf.cc base64-decode-udf.cc)

# Use the test harness.
add_executable(base64-encode-udf-test base64-encode-udf-test.cc)
target_link_libraries(base64-encode-udf-test ${UDF_LIBRARY} ImpalaUdf)
add_executable(base64-decode-udf-test base64-decode-udf-test.cc)
target_link_libraries(base64-decode-udf-test ${UDF_LIBRARY} ImpalaUdf)

enable_testing()

add_test(NAME base64-encode-udf-test COMMAND $<TARGET_FILE:base64-encode-udf-test>)
add_test(NAME base64-decode-udf-test COMMAND $<TARGET_FILE:base64-decode-udf-test>)

add_custom_target(tags ALL etags `find ${CMAKE_SOURCE_DIR} -name '*.hh' -o -name '*.cc'` WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
