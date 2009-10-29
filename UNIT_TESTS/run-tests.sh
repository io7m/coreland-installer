#!/bin/sh

EXIT_CODE=0

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
}

cleanup
mkdir installto || fatal "could not make installto"

echo "-- running basic tests"
./t_inst1.sh || failed
cleanup
mkdir installto || fatal "could not make installto"

./t_inst2.sh || failed
cleanup
mkdir installto || fatal "could not make installto"

./t_inst3.sh || failed
cleanup
mkdir installto || fatal "could not make installto"

./t_inst4.sh || failed

echo
cleanup

if [ ${EXIT_CODE} -eq 0 ]
then
  echo "Software passed all tests."
else
  echo "Software failed one or more tests."
fi

exit ${EXIT_CODE}
