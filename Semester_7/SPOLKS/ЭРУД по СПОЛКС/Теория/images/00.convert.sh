#!/bin/bash

DIRS=`ls -d */`
#DIRS=01/

for dr in $DIRS
do 
    cd $dr/
    echo ${dr}
    
    rm -f *.png
    
    PDF=`ls *.pdf`
    echo ${PDF}
    
    LKN=`pwd|awk -F "/" '{print $5}'`
    LK=lk$LKN
    
    cp -f ../lk.htm ./$LK.htm

    convert -density 205 $PDF $LK.%d.png

    PNGS=`ls -v *.png`
    COUNTER=0
    LINENUM=72
    for img in $PNGS
    do
#        echo "<img alt=\"Preview Image $COUNTER\" src=\"../images/$LK/$img\" data-image=\"../images/$LK/$img\">" >> 00.galery.js
	STRIMG="<img alt=\"Preview Image $COUNTER\" src=\"../images/$LK/$img\" data-image=\"../images/$LK/$img\">"

	sed -i $LINENUM"i $STRIMG" $LK.htm
        let COUNTER=COUNTER+1
        let LINENUM=LINENUM+1
    done

    cd ..
done