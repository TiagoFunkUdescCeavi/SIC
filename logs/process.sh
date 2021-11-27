#!/bin/bash

g++ process.cpp -o process

rm -f "results_2021_11_27.csv"
./process "log_2021_11_27.csv" >> "results_2021_11_27.csv"