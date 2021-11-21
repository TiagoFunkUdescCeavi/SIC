#!/bin/bash

execute_all(){
    for file in ./instances/*
    do
        if [ -f "$file" ]
        then
            for n in $(seq 1 $1)
            do
                echo "$n-$file"
                ./grasp/GRASP 1 1 1 $file --alpha 0.9 --iterations 5000 --path y --margin 1.9 --removeOperator r --removePercentage 0.15 --shuffleOperator e --addOperator b >> $2
            done
        fi
    done
}

n=4
log=log_2021_11_16.txt

execute_all $n $log
