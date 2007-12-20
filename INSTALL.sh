#!/bin/sh
# Utility script to add installer to a project

die()
{
  echo "fatal: $1" 1>&2
  exit 112
}
copy()
{
  echo "copy $1 $2"
  cp "$1" "$2" || die "could not copy"
}
makedir()
{
  echo "mkdir $1"
  mkdir "$1" # don't test for failure here as directory may exist already
}

make_fragment()
{
  file="$1"
  dep="$2"

  (printf "ctxt/$1.c: mk-ctxt $2\n"
   printf "\trm -f ctxt/$f.c\n"
   printf "\t./mk-ctxt ctxt_$f < $2 > ctxt/$f.c\n") > "ctxt/$f.mff.tmp" || die "could not make ctxt/$f.mff"

  mv "ctxt/$f.mff.tmp" "ctxt/$f.mff" || die "could not replace ctxt/$f.mff"
  touch "ctxt/$f.tbc" || die "could not create ctxt/$f.tbc"
}

if [ $# -ne 1 ]
then
  echo "usage: installer-repos" 1>&2
  exit 111
fi

repos=$1

copy ${repos}/deinstaller.c .
copy ${repos}/deinstaller.ld .
copy ${repos}/generic-conf.c .
copy ${repos}/inst-check.c .
copy ${repos}/inst-check.ld .
copy ${repos}/inst-copy.c .
copy ${repos}/inst-copy.ld .
copy ${repos}/inst-dir.c .
copy ${repos}/inst-dir.ld .
copy ${repos}/inst-link.c .
copy ${repos}/inst-link.ld .
copy ${repos}/install_core.c .
copy ${repos}/install_error.c .
copy ${repos}/installer.c .
copy ${repos}/installer.ld .
copy ${repos}/instchk.c .
copy ${repos}/instchk.ld .
copy ${repos}/insthier.c .
copy ${repos}/postinstall
copy ${repos}/Mkf-install
copy ${repos}/Mkf-deinstall
copy ${repos}/Mkf-instchk

makedir ctxt
for f in bindir dlibdir incdir repos slibdir
do
  make_fragment "${f}" "conf-${f}"
done
make_fragment "version" "VERSION"

(cat <<EOF
bindir.o
dlibdir.o
incdir.o
repos.o
slibdir.o
version.o
EOF
) > ctxt/ctxt.sld.tmp || die "could not create ctxt.sld.tmp"
mv ctxt/ctxt.sld.tmp ctxt/ctxt.sld || die "could not replace ctxt.sld"

(cat <<EOF
#ifndef CTXT_H
#define CTXT_H

extern char ctxt_version[];
extern char ctxt_bindir[];
extern char ctxt_dlibdir[];
extern char ctxt_slibdir[];
extern char ctxt_incdir[];
extern char ctxt_repos[];
extern char ctxt_owner[];
extern char ctxt_group[];

#endif
EOF
) > ctxt.h.tmp || die "could not create ctxt.h.tmp"
mv ctxt.h.tmp ctxt.h || die "could not replace ctxt.h"

