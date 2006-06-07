#!/bin/sh

cmp $1.exp $1.out
if [ $? -ne 0 ]
then
  echo 'Test failed' 2>&1
  exit 1
fi
