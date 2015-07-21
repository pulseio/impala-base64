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

#include "base64-decode-udf.hh"
#include "base64.hh"

StringVal pulse::base64::Decode(FunctionContext* ctx, const StringVal& s) {
  if (s.is_null) return StringVal::null();

  auto decoded = decode(s.ptr, s.len);

  StringVal result { ctx, static_cast<int>(decoded.size()) };
  memcpy(result.ptr, decoded.data(), result.len);

  return result;
}
