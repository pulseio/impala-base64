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

---

```
Copyright 2015 Google Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
