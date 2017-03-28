#!/bin/bash

if [ ! -f $1 ]; then
   echo "File $1 does not exist."
   exit 1
fi

if [ ! -d "$2" ]; then
    echo "Path $2 does not exist."
    exit 1
fi

#mv $1 $2
