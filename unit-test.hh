// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef PULSE_IMPALA_UNIT_TEST_H
#define PULSE_IMPALA_UNIT_TEST_H

#include <impala_udf/udf.h>

#include <sstream>
#include <stdexcept>

#define DIE(MSG) {                                      \
    std::ostringstream _msg;                            \
    _msg << __FILE__ << ':' << __LINE__ << ": " << MSG; \
    throw std::logic_error(_msg.str());                 \
  }

#define assertTrueMsg(M,...) { if (!(__VA_ARGS__)) DIE(M); }
#define assertFalseMsg(M,...) assertTrueMsg(M,!(__VA_ARGS__))

#define assertTrue(...) assertTrueMsg("'" #__VA_ARGS__ "' returned false",(__VA_ARGS__))
#define assertFalse(...) assertTrueMsg("'" #__VA_ARGS__ "' returned true",!(__VA_ARGS__))

#define assertEquals(A,B) {                                             \
    auto __a = (A);                                                     \
    auto __b = (B);                                                     \
    assertTrueMsg("Expected " << __a << ", got " << __b, __a == __b);   \
  }

#define RUN(X, ...)                                           \
  std::cout << #X "(" #__VA_ARGS__ ")" << " ... ";            \
  try {                                                       \
    X(__VA_ARGS__);                                           \
    std::cout << "OK" << std::endl;                           \
  }                                                           \
  catch (std::exception& ex) {                                \
    std::cout << "FAIL" << std::endl;                         \
    std::cerr << ex.what() << std::endl;                      \
    failures++;                                               \
  }

#endif
