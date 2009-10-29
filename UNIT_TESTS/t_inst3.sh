#!/bin/sh

fake_exec="files/t3/executable"

cleanup()
{
  rm -f "${fake_exec}"
}

die()
{
  echo "FAILED!"
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
echo '-- Testing fake root installation (missing directory) ./t_inst3'
rm -rf "installto/t3/fake_root" || die
./t_inst3

echo
echo '-- Testing fake root installation (not directory) ./t_inst3'
rm -rf "installto/t3/fake_root" || die
mkdir "installto/t3"            || die
touch "installto/t3/fake_root"  || die
./t_inst3

echo
echo '-- Testing fake root installation ./t_inst3'
rm -rf "installto/t3/fake_root" || die
mkdir "installto/t3/fake_root"  || die
./t_inst3 || die

echo
echo '-- Checking fake root installation ./t_instchk3'
./t_instchk3 || die

echo
echo '-- Checking fake root deinstallation ./t_deinst3'
./t_deinst3 || die

cleanup
