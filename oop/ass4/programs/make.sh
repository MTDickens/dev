#!/bin/bash

programs=("pdadd" "pdlist" "pdremove" "pdshow")

if [ "$1" == "del" ]; then
    for program in ${programs[@]}; do
        rm -f ${program}
    done
else
    if [ ! -d "./out" ]; then
        mkdir out
    fi
    for program in ${programs[@]}; do
        g++ -Werror -Wall -std=c++17 -O3 shared.cpp ${program}.cpp -o ./out/${program}
    done
fi
