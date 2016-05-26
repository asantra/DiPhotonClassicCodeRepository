#!/bin/bash

#Use the combine tool to take the counting_t6gg* files and turn them into limits
#mSquark bins
for i in {1200,1300,1400,1500,1550,1600,1650,1700,1750,1800,1850,1900,1950,2000}
do
    #mNeutralino bins
    for j in {100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000}
    do 
	if [ $j -lt $i ]
	then
	    combine -M Asymptotic counting_files/counting_t6gg_${i}_${j}.txt > limit_files/limit_t6gg_${i}_${j}.txt
	fi
    done
done
