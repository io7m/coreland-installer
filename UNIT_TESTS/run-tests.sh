#!/bin/sh

failed()
{
  echo "Software failed one or more tests."
  exit 112
}

echo "-- running basic tests"
rm -f t_inst1.out
./t_inst1.sh > t_inst1.out
cmp t_inst1.out t_inst1.exp
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
