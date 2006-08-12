#!/bin/sh

failed()
{
  echo "Software failed one or more tests."
  exit 112
}

echo "-- running basic tests"
./t_inst1.sh
if [ $? -ne 0 ]
then
  failed
fi

./t_inst2.sh
if [ $? -ne 0 ]
then
  failed
fi

echo "Software passed all tests."
exit 0
