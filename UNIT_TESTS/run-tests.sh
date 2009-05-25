#!/bin/sh

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
  echo "Software failed one or more tests."
  cleanup
  exit 112
}

cleanup
mkdir installto || fatal "could not make installto"

echo "-- running basic tests"
./t_inst1.sh
if [ $? -ne 0 ]
then
  failed
fi

cleanup
mkdir installto || fatal "could not make installto"

./t_inst2.sh
if [ $? -ne 0 ]
then
  failed
fi

cleanup
mkdir installto || fatal "could not make installto"

./t_inst3.sh
if [ $? -ne 0 ]
then
  failed
fi

echo
echo "Software passed all tests."
cleanup
exit 0
