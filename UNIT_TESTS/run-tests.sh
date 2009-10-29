#!/bin/sh

EXIT_CODE=0
TEST_COUNT=0
TEST_FAIL=0

fatal()
{
  echo "fatal: $1" 1>&2
  exit 112
}

cleanup()
{
  rm -rf installto || fatal "could not remove installto"
}

failed()
{
  EXIT_CODE=1
  TEST_FAIL=`expr ${TEST_FAIL} + 1` || fatal "could not increment test count"
}

try()
{
  TEST="$1"

  cleanup
  mkdir installto || fatal "could not make installto"

  TEST_COUNT=`expr ${TEST_COUNT} + 1` || fatal "could not increment test count"

  cat <<EOF

#
# TEST ${TEST_COUNT}
#
EOF

  ${TEST} || failed
}

cleanup
mkdir installto || fatal "could not make installto"

try ./t_inst1.sh 
try ./t_inst2.sh
try ./t_inst3.sh
try ./t_inst4.sh

cleanup

cat <<EOF

Tests  : ${TEST_COUNT}
Failed : ${TEST_FAIL}
EOF

exit ${EXIT_CODE}
