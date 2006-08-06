#!/bin/sh

# cannot compare output of this script due to name differences in
# shared libraries across platforms.

echo '-- testing shared library installation'
./t_inst2
if [ $? -ne 0 ]
then
  echo "test failed, please report this bug."
  exit 1
fi

echo '-- checking shared library installation'
./t_instchk2
if [ $? -ne 0 ]
then
  echo "test failed, please report this bug."
  exit 1
fi

echo '-- testing shared library deinstallation'
./t_deinst2
if [ $? -ne 0 ]
then
  echo "test failed, please report this bug."
  exit 1
fi
