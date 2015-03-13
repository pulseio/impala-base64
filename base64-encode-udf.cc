#include "base64-encode-udf.hh"
#include "base64.hh"

StringVal pulse::base64::Encode(FunctionContext* ctx, const StringVal& s) {
  if (s.is_null) return StringVal::null();

  auto encoded = encode(s.ptr, s.len);

  StringVal result { ctx, static_cast<int>(encoded.size()) };
  memcpy(result.ptr, encoded.data(), result.len);

  return result;
}
