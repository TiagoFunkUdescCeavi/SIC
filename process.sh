#!/bin/bash

g++ process.cpp -o process

rm "results.csv"
./process "log_2021_11_16.csv" >> "results.csv"