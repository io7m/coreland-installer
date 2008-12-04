#!/bin/sh

fatal()
{
  echo "fatal: $1" 1>&2
  exit 112
}

IGNORE="
_sd_*.h
_sysinfo.h
ctxt.h
ctxt.sld
deinstaller.c
deinstaller.ld
install-error.c
install-posix.c
install-win32.c
install-core.c
install.h
install.sld
install_os.h
installer.c
installer.ld
instchk.c
instchk.ld
insthier.c
mk-ctxt.c
mk-ctxt.ld
sd_*.h
"

FILES=`ls *.c`
FILES="$FILES `ls *.ads 2>/dev/null`"
FILES="$FILES `ls *.adb 2>/dev/null`"
FILES="$FILES `ls *.ali 2>/dev/null`"
FILES="$FILES `ls *.h 2>/dev/null`"
FILES="$FILES `ls *.sld 2>/dev/null`"
FILES="$FILES `ls *.dld 2>/dev/null`"
FILES="$FILES `ls *.ld 2>/dev/null`"

bindir="ctxt_bindir"
incdir="ctxt_incdir"
dlibdir="ctxt_dlibdir"
slibdir="ctxt_slibdir"
repos="ctxt_repos"

cat <<EOF
  {INST_MKDIR, 0, 0, ctxt_bindir, 0, 0, 0755},
  {INST_MKDIR, 0, 0, ctxt_incdir, 0, 0, 0755},
  {INST_MKDIR, 0, 0, ctxt_dlibdir, 0, 0, 0755},
  {INST_MKDIR, 0, 0, ctxt_slibdir, 0, 0, 0755},
  {INST_MKDIR, 0, 0, ctxt_repos, 0, 0, 0755},
EOF

for file in $FILES
do
  no=0
  slib=0
  dlib=0
  head=0
  exec=0
  alif=0

  for ign in $IGNORE
  do
    if [ "$ign" = "$file" ]; then no=1; break; fi
  done

  if [ $no -ne 0 ]; then continue; fi

  suf=`echo $file | awk -F. '{print $NF}'`
  pre=`echo $file | awk -F. '{print $1}'`

  if [ "$suf" = "ld" ]; then exec=1; fi
  if [ "$suf" = "sld" ]; then slib=1; fi
  if [ "$suf" = "dld" ]; then dlib=1; fi
  if [ "$suf" = "h" ]; then head=1; fi
  if [ "$suf" = "ads" ]; then head=1; fi
  if [ "$suf" = "adb" ]; then head=1; fi
  if [ "$suf" = "ali" ]; then alif=1; fi

  cat <<EOF
  {INST_COPY, "$pre.$suf", 0, $repos, 0, 0, 0644},
EOF

  if [ $dlib -eq 1 ]
  then
    full=`cat $pre.vlb`
    if [ $? -ne 0 ] || [ -z "${full}" ]
    then
      fatal "could not read library name"
    fi
  cat <<EOF
  {INST_COPY, "${full}", "lib${full}", $dlibdir, 0, 0, 0644},
EOF
  fi

  if [ $slib -eq 1 ]
  then
  cat <<EOF
  {INST_COPY, "$pre.a", "lib$pre.a", $slibdir, 0, 0, 0644},
EOF
  fi

  if [ $alif -eq 1 ]
  then
  cat <<EOF
  {INST_COPY, "$pre.$suf", 0, $incdir, 0, 0, 0444},
EOF
  fi

  if [ $head -eq 1 ]
  then
  cat <<EOF
  {INST_COPY, "$pre.$suf", 0, $incdir, 0, 0, 0644},
EOF
  fi

  if [ $exec -eq 1 ]
  then
  cat <<EOF
  {INST_COPY_EXEC, "$pre", 0, $bindir, 0, 0, 0755},
EOF
  fi

done
