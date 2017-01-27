#!/bin/bash

ls | grep jpg > a #the list of filenames that contains jpg
a1=$(cat a) #string version of a
cat a | cut -d'.' -f1 > a0 #get the list of filenames with suffix striped
a2=$(cat a0) # string version of a0

ls | grep dat > b # list of filenames containing dat
b1=$(cat b) # string version of b

imagenames=""
for f in ${a2}
do
	if [[ ${b1} == *"${f}"* ]];
	then 
	imagenames="${imagenames} ${f}".jpg""
	fi 

done

#only the jpg files that have a matching dat file will be returned


while [ 1 ]
do
	p=`ps -C eog --no-headers | wc -l` #p is the number of opening pictures
	if [ "$p" -eq "$1" ]
	then
		continue
	fi

	this_imagename=`echo ${imagenames} | cut -d' ' -f1` 
	#find the first picture in the waiting list

	imagenames="`echo ${imagenames} | cut -d' ' -f2-` ${this_imagename}"
	#adjust waitlist

	eog -n ${this_imagename} & #display it

done
