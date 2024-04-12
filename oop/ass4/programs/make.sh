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
        if [ "$1" == "block" ]; then
            g++ -Werror -Wall -std=c++17 -O2 -DBLOCK_CLOG shared.cpp ${program}.cpp -o ./out/${program}
        else
            g++ -Werror -Wall -std=c++17 -O2 shared.cpp ${program}.cpp -o ./out/${program}
        fi
    done
fi
