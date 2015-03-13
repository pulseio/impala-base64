# impala-base64

Impala Base64 UDF implementation.

Impala Base64 UDF Installation
------------------------------

1. Copy shared library to HDFS as `/user/pulse/lib/impala/libPulseB64Udf.so`
2. `CREATE FUNCTION encode64(STRING) RETURNS STRING
   LOCATION '/user/pulse/lib/impala/libPulseB64Udf.so'
   UPDATE_FN='pulse::base64::Encode';`
3. `CREATE FUNCTION decode64(STRING) RETURNS STRING
   LOCATION '/user/pulse/lib/impala/libPulseB64Udf.so'
   UPDATE_FN='pulse::base64::Decode';`

These steps are encoded in the script `install.sh`.  By default, `install.sh` will install the release build; set the environment variable `BUILD` to `Debug` (case-sensitive) to install the debugging build.

