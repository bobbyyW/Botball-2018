#!/bin/bash

if [ $# -ne 1 ] ; then
  echo "Example:"
  echo "cd ~/Botball-2018/Wallaby/src"
  echo "./scripts/upload.sh Austin/Wallaby/src"
  exit 1;
fi

scp -r . root@192.168.125.1:"Documents/KISS/$1/"

exit 0;

