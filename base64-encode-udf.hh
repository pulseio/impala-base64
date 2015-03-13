#ifndef PULSE_IMPALA_B64_ENCODE_UDF_H
#define PULSE_IMPALA_B64_ENCODE_UDF_H

#include <impala_udf/udf.h>

using impala_udf::FunctionContext;
using impala_udf::StringVal;

namespace pulse {
  namespace base64 {
    StringVal Encode(FunctionContext* ctx, const StringVal& s);
  }
}

#endif
