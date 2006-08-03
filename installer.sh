#!/bin/sh

fatal()
{
  echo "installer: fatal: $1" 1>&2
  exit 112
}
error()
{
  echo "installer: error: $1" 1>&2
}
error()
{
  echo "installer: warn: $1" 1>&2
}

IFS="
"

libname="./libname"
insthier="insthier"
copy="./inst-copy"
dryrun=0
if [ ! -z "$1" ]
then
  dryrun=1
fi

getuid="./inst-uid"
getgid="./inst-gid"

if [ ! -f ${insthier} ]
then
  fatal "could not open insthier"
fi
if [ ! -f ${libname} ]
then
  fatal "libname support script is missing"
fi

#
# main loop
#

for f in `cat ${insthier}`
do
  op=`echo $f | awk -F: '{print $1}'`
  src=`echo $f | awk -F: '{print $2}'`
  dst=`echo $f | awk -F: '{print $3}'`
  dir=`echo $f | awk -F: '{print $4}'`
  owner=`echo $f | awk -F: '{print $5}'`
  group=`echo $f | awk -F: '{print $6}'`
  perm=`echo $f | awk -F: '{print $7}'`

  # sanity

  if [ -z "${op}" ]
  then
    error "no operation specified"
    continue
  fi
  if [ -z "${src}" ]
  then
    error "no source file specified"
    continue
  fi
  if [ -z "${owner}" ]
  then
    uid=-1
  else
    uid=`${getuid} ${owner}`
    if [ $? -ne 0 ]
    then
      continue
    fi
  fi
  if [ -z "${group}" ]
  then
    gid=-1
  else
    gid=`${getgid} ${group}`
    if [ $? -ne 0 ]
    then
      continue
    fi
  fi
  if [ -z ${perm} ]
  then
    perm=-1
  fi
 
  # filename conversions

  suffix=`echo ${src} | awk -F. '{print $NF}'`
  if [ "${suffix}" = "lib" ]
  then
    src=`cat ${src}`
    if [ $? -ne 0 ]
    then
      fatal "could not read lib file \"${src}\""
    fi
  fi
 
  if [ -z ${dst} ]
  then
    dst=`basename ${src}`
  fi

  case ${op} in
    copy)
      "${copy}" "$src" "$dir/$dst" $uid $gid $perm
      ;;
    *) warn "unknown operator ignored"
       continue
      ;;
  esac
done
