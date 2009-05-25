#!/bin/sh

fake_exec="files/t3/executable"

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
echo '-- testing fake root installation (missing directory) ./t_inst3'
rm -rf "installto/t3/fake_root" || die
./t_inst3
if [ $? -eq 0 ]
then
  echo "test failed, please report this bug."
  exit 1
fi

echo
echo '-- testing fake root installation (not directory) ./t_inst3'
rm -rf "installto/t3/fake_root" || die
mkdir -p "installto/t3"         || die
touch "installto/t3/fake_root"  || die
./t_inst3
if [ $? -eq 0 ]
then
  echo "test failed, please report this bug."
  die
fi

echo
echo '-- testing fake root installation ./t_inst3'
rm -rf "installto/t3/fake_root"   || die
mkdir -p "installto/t3/fake_root" || die
./t_inst3
if [ $? -ne 0 ]
then
  echo "test failed, please report this bug."
  die
fi

echo
echo '-- checking fake root installation ./t_instchk3'
./t_instchk3
if [ $? -ne 0 ]
then
  echo "test failed, please report this bug."
  die
fi

echo
echo '-- checking fake root deinstallation ./t_deinst3'
./t_deinst3
if [ $? -ne 0 ]
then
  echo "test failed, please report this bug."
  die
fi
