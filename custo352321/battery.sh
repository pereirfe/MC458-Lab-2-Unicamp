#!/bin/bash

if [ $# -ne 2 ] 
then
    echo 'Uso: bash battery $number $out_file'

else 

    for i in {1..100}
    do
	it=`echo "$i * 50" | bc` 
	
	for times in {0..4}
	do
	    STR="ins.${it}.${times}.${1}.txt"
	    echo $STR
	    (time -p `./editdistance_mes < "ins.${it}.${1}.${times}.txt"` ) 2>&1 | grep user | cut -c 6- | tr -d '\n' >> $2
	    echo -ne ";" >> $2
	done
	echo "" >> $2
    done
fi
