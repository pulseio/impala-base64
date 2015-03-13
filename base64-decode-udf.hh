#ifndef PULSE_IMPALA_B64_DECODE_UDF_H
#define PULSE_IMPALA_B64_DECODE_UDF_H

#include <impala_udf/udf.h>

using impala_udf::FunctionContext;
using impala_udf::StringVal;

namespace pulse {
  namespace base64 {
    StringVal Decode(FunctionContext* ctx, const StringVal& s);
  }
}

#endif
