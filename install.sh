#!/bin/sh

GIT_TAG=`git describe --dirty 2>/dev/null`

set -e

# If you change LIBDIR, you need to restart Impala!
LIBDIR=/user/pulse/lib/impala
LIBRARY=libPulseB64Udf${GIT_TAG:+-${GIT_TAG}}.so

[ -f ${BUILD:=Release}/build/$LIBRARY ] || ./build.sh

impala-shell -d "${DATABASE:=pulse}" -q 'DROP FUNCTION IF EXISTS encode64(STRING); DROP FUNCTION IF EXISTS decode64(STRING)'

echo Installing library $LIBRARY to $LIBDIR ...

hdfs dfs -mkdir -p "$LIBDIR"
hdfs dfs -put -f "$BUILD/build/$LIBRARY" "$LIBDIR/"

impala-shell -d "$DATABASE" -q "CREATE FUNCTION encode64(STRING) RETURNS STRING LOCATION '$LIBDIR/$LIBRARY' SYMBOL='pulse::base64::Encode'; CREATE FUNCTION decode64(STRING) RETURNS STRING LOCATION '$LIBDIR/$LIBRARY' SYMBOL='pulse::base64::Decode'"

echo Done
