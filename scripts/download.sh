#!/bin/bash

if [ $# -ne 1 ] ; then
  echo "Example:"
  echo "cd /Users/austinwang/Botball-2018/Wallaby"
  echo "/Users/austinwang/Botball-2018/scripts/download.sh Austin/Wallaby/src"
  exit 1;
fi

scp -r root@192.168.125.1:"Documents/KISS/$1" ./

exit 0;

