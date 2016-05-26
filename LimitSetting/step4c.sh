#!/bin/bash    
#Take the limit files and convert them into limit histograms
#mSquark bins  
for i in {1200,1300,1400,1500,1550,1600,1650,1700,1750,1800,1850,1900,1950,2000}
do
    #mNeutralino bins
    for j in {100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000}
    do
        if [ $j -lt $i ]
        then
	    FILE_NAME=limit_files/limit_t6gg_${i}_${j}.txt
	    TEST_STRING2=$(grep 'Expected 16.0%:' $FILE_NAME)
	    if [ ${#TEST_STRING2} -gt 0 ]
	    then
		sed -i "/Test/ a\
hExpLimDown->SetBinContent(hExpLimDown->GetXaxis()->FindBin(${i}), hExpLimDown->GetYaxis()->FindBin(${j}), ${TEST_STRING2:20:7});" ExpLimDown.C
	    fi
        fi
    done
done
