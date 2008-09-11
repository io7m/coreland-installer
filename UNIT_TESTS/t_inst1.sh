#!/bin/sh

exec 2>&1

echo
echo '-- files do not exist before testing'
./t_instchkpre
if [ $? -ne 0 ]
then
  exit 1
fi

echo
echo '-- deinstaller objects to removing nonexistant files'
./t_deinst12
if [ $? -ne 0 ]
then
  exit 1
fi

echo
echo '-- installer installs files, directories and symlinks'
./t_inst1
if [ $? -ne 0 ]
then
  exit 1
fi

echo
echo '-- instchk checks existence and attributes'
./t_instchk1
if [ $? -ne 0 ]
then
  exit 1
fi

echo
echo '-- deinstaller removes files, directories and symlinks'
./t_deinst1
if [ $? -ne 0 ]
then
  exit 1
fi

echo
echo '-- files have definitely been removed '
./t_deinst12
if [ $? -ne 0 ]
then
  exit 1
fi

