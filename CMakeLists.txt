# Copyright 2015 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
