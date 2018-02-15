#!/bin/bash

path="Default\ User/gcer\ 2017"

if [ $# -eq 2 ]; then
  path=$2
fi

scp -r root@$1:"Documents/KISS/$path" ./

exit 0;

