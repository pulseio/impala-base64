#include "base64-decode-udf.hh"
#include "base64.hh"

StringVal pulse::base64::Decode(FunctionContext* ctx, const StringVal& s) {
  if (s.is_null) return StringVal::null();

  auto decoded = decode(s.ptr, s.len);

  StringVal result { ctx, static_cast<int>(decoded.size()) };
  memcpy(result.ptr, decoded.data(), result.len);

  return result;
}
