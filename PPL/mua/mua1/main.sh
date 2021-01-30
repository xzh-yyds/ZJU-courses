#!/bin/bash
function itdir(){
    rm -f *.class
    for element in `ls`
    do  
        if [ -d $element ]
        then
            cd $element
            itdir $element
            cd ..
        fi  
    done
}

#echo "cleaning"
itdir "."
#echo "compiling"
javac -cp .:src Test.java
#echo "executing"
java -cp .:src Test $1
#cat $1
#echo "cleaning"
#itdir "."
