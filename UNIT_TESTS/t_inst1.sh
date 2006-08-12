#!/bin/sh

exec 2>&1

echo '-- files do not exist before testing'
./t_instchk1
echo

echo '-- deinstaller objects to removing nonexistant files'
./t_deinst1
echo

echo '-- installer installs files, directories and symlinks'
./t_inst1
echo

echo '-- instchk checks existence and attributes'
./t_instchk1
echo

echo '-- deinstaller removes files, directories and symlinks'
./t_deinst1
echo

echo '-- files have definitely been removed '
./t_instchk1
echo
