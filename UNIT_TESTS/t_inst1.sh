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
echo '-- Creating fake executable'
systype="`cat conf-systype`" || die
if [ "${systype}" = "MS_WINDOWS" ]
then
  fake_exec="${fake_exec}.exe"
fi
echo 'Joy!peffpwpc' > "${fake_exec}" || die
echo "${fake_exec}"

echo
echo '-- Files do not exist before testing ./t_instchkpre'
./t_instchkpre || die

echo
echo '-- Deinstaller objects to removing nonexistant files ./t_deinst12'
./t_deinst12 || die

echo
echo '-- Installer installs files, directories and symlinks ./t_inst1'
./t_inst1 || die

echo
echo '-- instchk checks existence and attributes ./t_instchk1'
./t_instchk1 || die

echo
echo '-- Deinstaller removes files, directories and symlinks ./t_deinst1'
./t_deinst1 || die

echo
echo '-- Files have definitely been removed ./t_deinst12'
./t_deinst12 || die

cleanup
