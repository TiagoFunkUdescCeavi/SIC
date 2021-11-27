#!/bin/bash

execute_all(){
    for file in ../instances/*
    do
        if [ -f "$file" ]
        then
            for n in $(seq 1 $1)
            do
                echo "$n-$file"
                ../project/APP 1 1 1 $file --algorithm genetic --alpha 0.9 --margin 1.0 --iterations 5000 --populationSize 30 --rate 0.3 --removePercentage 0.15 >> $2
            done
        fi
    done
}

n=4
log=log_2021_11_27.csv

execute_all $n $log
