#!/bin/bash

#Run "create_lib.sh" on all library directories

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

