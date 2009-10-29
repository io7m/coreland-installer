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
echo '-- Testing shared library installation ./t_inst4'
./t_inst4 || exit 1

echo
echo '-- Checking shared library installation ./t_instchk4'
./t_instchk4 || exit 1

echo
echo '-- Testing shared library deinstallation ./t_deinst4'
./t_deinst4 || exit 1

rm -f "files/t4/t4.${suffix}"
rm -f "files/t4/t4.vlb"
