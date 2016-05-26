#!/bin/bash

#Run "create_lib.sh" on all library directories

mkdir ../lib

CPLUS_INCLUDE_PATH=`pwd`
export CPLUS_INCLUDE_PATH

for i in `find -maxdepth 1 -type d`
do
	if [ $i = "." ]
	then
		echo "."
	else
		cd $i
		pwd
		./create_lib.sh
		cd ..
	fi
done

