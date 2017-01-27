#!/bin/bash

ls | grep jpg > a #the list of filenames that contains jpg
a1=$(cat a) #string version of a
cat a | cut -d'.' -f1 > a0 #get the list of filenames with suffix striped
a2=$(cat a0) # string version of a0

ls | grep dat > b # list of filenames containing dat
b1=$(cat b) # string version of b

names=""
for f in ${a2}
do
	if [[ ${b1} == *"${f}"* ]];
	then 
	names="${names} ${f}"
	fi 

done

#only the filenames that have a matching dat file will be returned

	
if [ $1 == "alpha" ]
then
	for f in $names; do echo $f >> a.txt; done
	sort a.txt > a1.txt
	cat a1.txt

	line1=$(head -n 1 a1.txt)
	cp ${line1}".jpg" result.jpg
	echo "$(tail -n +2 a1.txt)" > a1.txt

	while IFS='' read -r line || [[ -n "$line" ]]
	do	
		t=${line}".jpg"
		convert result.jpg ${t} -append result.jpg	
	done < a1.txt

	eog -n result.jpg &
	rm a.txt a1.txt 
fi


if [ $1 == "weight" ]
then
	for f in $names; do echo $f `cat ${f}.dat` >> b.txt; done
	cat b.txt | sort -k2 -n | cut -d' ' -f1 > b1.txt
	cat b1.txt

	line1=$(head -n 1 b1.txt)
	cp ${line1}".jpg" result.jpg
	echo "$(tail -n +2 b1.txt)" > b1.txt

	while IFS='' read -r line || [[ -n "$line" ]]
	do	
		t=${line}".jpg"
		convert result.jpg ${t} -append result.jpg	
	done < b1.txt

	eog -n result.jpg &
	rm b.txt b1.txt
fi

if [ $1 == "length" ]
then
	for f in $names; do echo $f `cat ${f}.dat` >> c.txt; done
	cat c.txt | sort -k3 -n | cut -d' ' -f1 > c1.txt
	cat c1.txt

	line1=$(head -n 1 c1.txt)
	cp ${line1}".jpg" result.jpg
	echo "$(tail -n +2 c1.txt)" > c1.txt

	while IFS='' read -r line || [[ -n "$line" ]]
	do	
		t=${line}".jpg"
		convert result.jpg ${t} -append result.jpg	
	done < c1.txt

	eog -n result.jpg &
	rm c.txt c1.txt
	
fi

#to make the test convient, the following part of code can remove the result.jpg after all the eog windows have been colsed. 

#close the window and it will quit

while [ 1 ]
do  
ps=`ps -C eog --noheaders | wc -l`
	if [ $ps -eq 0 ]
	then
		rm result.jpg	
		break
	fi
done

rm a a0 b

