#!/bin/sh

fake_exec="files/t1/executable"

cleanup()
{
  rm -f "${fake_exec}"
}

die()
{
  cleanup
  exit 1
}

exec 2>&1

echo
echo '-- creating fake executable'
systype="`cat conf-systype`" || die
if [ "${systype}" = "MS_WINDOWS" ]
then
  fake_exec="${fake_exec}.exe"
fi
echo 'Joy!peffpwpc' > "${fake_exec}" || die
echo "${fake_exec}"

echo
echo '-- files do not exist before testing ./t_instchkpre'
./t_instchkpre
if [ $? -ne 0 ]
then
  die
fi

echo
echo '-- deinstaller objects to removing nonexistant files ./t_deinst12'
./t_deinst12
if [ $? -ne 0 ]
then
  die
fi

echo
echo '-- installer installs files, directories and symlinks ./t_inst1'
./t_inst1
if [ $? -ne 0 ]
then
  die
fi

echo
echo '-- instchk checks existence and attributes ./t_instchk1'
./t_instchk1
if [ $? -ne 0 ]
then
  die
fi

echo
echo '-- deinstaller removes files, directories and symlinks ./t_deinst1'
./t_deinst1
if [ $? -ne 0 ]
then
  die
fi

echo
echo '-- files have definitely been removed ./t_deinst12'
./t_deinst12
if [ $? -ne 0 ]
then
  die
fi

cleanup
