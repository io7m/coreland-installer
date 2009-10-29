#!/bin/sh

# cannot compare output of this script due to name differences in
# shared libraries across platforms.

suffix="`cat conf-sosuffix`"
echo  "files/t2/t2.${suffix}" > "files/t2/t2.vlb"
touch "files/t2/t2.${suffix}"

echo
echo '-- Testing shared library installation ./t_inst2'
./t_inst2 || exit 1

echo
echo '-- Checking shared library installation ./t_instchk2'
./t_instchk2 || exit 1

echo
echo '-- Testing shared library deinstallation ./t_deinst2'
./t_deinst2 || exit 1

rm -f "files/t2/t2.${suffix}"
rm -f "files/t2/t2.vlb"
