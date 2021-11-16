#!/bin/bash

execute_all(){
    for file in ./instances/*
    do
        if [ -f "$file" ]
        then
            for n in $(seq 1 $1)
            do
                echo "$n-$file"
                ./grasp/GRASP 1 1 1 $file --alpha 0.9 --iterations 50000 --path y --margin 1.9 --removeOperator r --removePercentage 0.15 --shuffleOperator e --addOperator b >> $2
            done
        fi
    done
}

n=5
log=log.txt

execute_all $n $log
