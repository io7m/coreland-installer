#!/bin/sh
# Utility script to add installer to a project

info()
{
  echo "info: $1" 1>&2
}

die()
{
  echo "fatal: $1" 1>&2
  exit 112
}
copy()
{
  echo "copy $1 $2"
  cp -f "$1" "$2" || die "could not copy"
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
  mff_file="${file}.c.mff"
  tbc_file="${file}.c.tbc"

  info "create ctxt/$mff_file"
  (printf "ctxt/${file}.c: mk-ctxt ${dep}\n"
   printf "\trm -f ctxt/${file}.c\n"
   printf "\t./mk-ctxt ctxt_${file} < ${dep} > ctxt/${file}.c\n") > "ctxt/${mff_file}.tmp" ||
    die "could not make ctxt/${mff_file}"
  mv "ctxt/${mff_file}.tmp" "ctxt/${mff_file}" ||
    die "could not replace ctxt/${mff_file}"

  info "create ctxt/$tbc_file"
  touch "ctxt/${tbc_file}" || die "could not create ctxt/${tbc_file}"
}

if [ $# -ne 1 ]
then
  echo "usage: installer-repos" 1>&2
  exit 111
fi

repos=$1

copy ${repos}/Mkf-deinstall
copy ${repos}/Mkf-install
copy ${repos}/Mkf-instchk
copy ${repos}/deinstaller.c
copy ${repos}/deinstaller.ld
copy ${repos}/generic-conf.c
copy ${repos}/install-core.c
copy ${repos}/install-posix.c
copy ${repos}/install-win32.c
copy ${repos}/install.h
copy ${repos}/install.sld
copy ${repos}/install_os.h
copy ${repos}/installer.c
copy ${repos}/installer.ld
copy ${repos}/instchk.c
copy ${repos}/instchk.ld
copy ${repos}/insthier.c
copy ${repos}/postinstall

makedir ctxt
for f in bindir dlibdir incdir repos slibdir fakeroot
do
  make_fragment "${f}" "conf-${f}"
done

make_fragment "version" "VERSION"

if [ ! -f ctxt/ctxt.sld ]
then
  (cat <<EOF
bindir.o
dlibdir.o
fakeroot.o
incdir.o
repos.o
slibdir.o
version.o
EOF
) > ctxt/ctxt.sld || die "could not create ctxt.sld"
fi

if [ ! -f ctxt.h ]
then
  (cat <<EOF
#ifndef CTXT_H
#define CTXT_H

extern char ctxt_bindir[];
extern char ctxt_dlibdir[];
extern char ctxt_fakeroot[];
extern char ctxt_group[];
extern char ctxt_incdir[];
extern char ctxt_owner[];
extern char ctxt_repos[];
extern char ctxt_slibdir[];
extern char ctxt_version[];

#endif
EOF
) > ctxt.h || die "could not create ctxt.h"
fi

if [ ! -f insthier.c ]
then
  (cat <<EOF
#include "ctxt.h"
#include "install.h"

struct install_item insthier[] = {

};
unsigned long insthier_len = sizeof(insthier) / sizeof(struct install_item);
EOF
) > insthier.c || die "could not create insthier.c"
fi
