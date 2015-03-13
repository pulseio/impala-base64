#include "base64-decode-udf.hh"
#include "unit-test.hh"

#include <impala_udf/udf-test-harness.h>

using namespace impala_udf;
using pulse::base64::Decode;

#define Harness UdfTestHarness::ValidateUdf<StringVal,StringVal>

void test1() {
  assertTrue(Harness(&Decode, StringVal::null(), StringVal::null())); 
}

void test2() {
  auto arg = "SGVsbG8gd29ybGQ=";
  auto expected = "Hello world";

  assertTrue(Harness(&Decode, arg, expected));
}

void test3() {
  auto arg = "AAECAwQ=";
  uint8_t expected[] = { 0, 1, 2, 3, 4 };

  assertTrue(Harness(&Decode, arg, StringVal(expected, sizeof(expected))));
}

int main() {
  int failures = 0;

  RUN(test1);
  RUN(test2);
  RUN(test3);

  return failures != 0;
}
