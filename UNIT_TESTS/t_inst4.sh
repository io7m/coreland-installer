#!/bin/sh

# cannot compare output of this script due to name differences in
# shared libraries across platforms.

suffix="`cat conf-sosuffix`"
echo  "files/t4/t4.${suffix}" > "files/t4/t4.vlb"
touch "files/t4/t4.${suffix}"

rm -rf "installto"

mkdir "installto"
mkdir "installto/t4"
mkdir "installto/t4/fake_root"

echo
echo '-- testing shared library installation ./t_inst4'
./t_inst4
if [ $? -ne 0 ]
then
  echo "test failed, please report this bug."
  exit 1
fi

echo
echo '-- checking shared library installation ./t_instchk4'
./t_instchk4
if [ $? -ne 0 ]
then
  echo "test failed, please report this bug."
  exit 1
fi

echo
echo '-- testing shared library deinstallation ./t_deinst4'
./t_deinst4
if [ $? -ne 0 ]
then
  echo "test failed, please report this bug."
  exit 1
fi

rm -f "files/t4/t4.${suffix}"
rm -f "files/t4/t4.vlb"
