#!/bin/sh

# cannot compare output of this script due to name differences in
# shared libraries across platforms.

suffix="`cat conf-sosuffix`"
echo  "files/t2/t2.${suffix}" > "files/t2/t2.vlb"
touch "files/t2/t2.${suffix}"

echo
echo '-- testing shared library installation ./t_inst2'
./t_inst2
if [ $? -ne 0 ]
then
  echo "test failed, please report this bug."
  exit 1
fi

echo
echo '-- checking shared library installation ./t_instchk2'
./t_instchk2
if [ $? -ne 0 ]
then
  echo "test failed, please report this bug."
  exit 1
fi

echo
echo '-- testing shared library deinstallation ./t_deinst2'
./t_deinst2
if [ $? -ne 0 ]
then
  echo "test failed, please report this bug."
  exit 1
fi

rm -f "files/t2/t2.${suffix}"
rm -f "files/t2/t2.vlb"
