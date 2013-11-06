#!/bin/bash

if [ $# -ne 1 ] 
then
    echo 'Uso: bash battery $out_file'

else 

    for i in {1..100}
    do
	it=`echo "$i * 50" | bc` 
	
	for times in {0..4}
	do
	    STR="ins.dna.${it}.${times}.txt"
	    echo $STR
	    (time -p `./qb_mes < "ins.dna.${it}.${times}.txt"` ) 2>&1 |grep user|cut -c 6-| tr -d '\n' >> $1
	    echo -ne ";" >> $1
	done
	echo "" >> $1
    done
fi
