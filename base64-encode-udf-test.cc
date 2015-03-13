#include "base64-encode-udf.hh"
#include "unit-test.hh"

#include <impala_udf/udf-test-harness.h>

using namespace impala_udf;
using pulse::base64::Encode;

#define Harness UdfTestHarness::ValidateUdf<StringVal,StringVal>

void test1() {
  assertTrue(Harness(&Encode, StringVal::null(), StringVal::null())); 
}

void test2() {
  auto arg = "Hello world";
  auto expected = "SGVsbG8gd29ybGQ=";

  assertTrue(Harness(&Encode, arg, expected));
}

void test3() {
  uint8_t arg[] = { 0, 1, 2, 3, 4 };
  auto expected = "AAECAwQ=";

  assertTrue(Harness(&Encode, StringVal(arg, sizeof(arg)), expected));
}

int main() {
  int failures = 0;

  RUN(test1);
  RUN(test2);
  RUN(test3);

  return failures != 0;
}
