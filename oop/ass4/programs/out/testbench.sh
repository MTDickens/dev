#!/bin/bash

# Testbench for pdadd, pdlist, pdremove, and pdshow

## Clear diary.dat
echo -n "0\n" > diary.dat

## test pdadd
printf "\e[1;31mTesting pdadd\e[0m\n"
printf "\e[1;34m./pdadd today\e[0m\n"
printf "Today\nTest" | ./pdadd "today"
printf "\e[1;34m./pdadd 20240401\e[0m\n"
printf "April 1st, 2024\nApril Fool's Day\n." | ./pdadd 20240401
printf "\e[1;34m./pdadd 19491001\e[0m\n"
printf "October 1st, 1949\nPeople's Republic of China was founded" | ./pdadd 19491001
printf "\e[1;34m./pdadd 19111010\e[0m\n"
printf "October 10th, 1911\nXinhai Revolution" | ./pdadd 19111010

## test pdlist
printf "\n\e[1;31mTesting pdlist\e[0m\n"
printf "\e[1;34m./pdlist\e[0m\n"
./pdlist
printf "\e[1;34m./pdlist 19490101\e[0m\n"
./pdlist 19490101 ## 19490101 onwards
printf "\e[1;34m./pdlist 19110206 20240331\e[0m\n"
./pdlist 19110206 20240331 ## From 19110206 to 20240331
printf "\e[1;34m./pdlist 99991010\e[0m\n"
./pdlist 99991010 ## Test non-existent date

## test pdshow
printf "\n\e[1;31mTesting pdshow\e[0m\n"
printf "\e[1;34m./pdshow today\e[0m\n"
./pdshow today ## Today
printf "\e[1;34m./pdshow 20240401\e[0m\n"
./pdshow 20240401 ## April 1st, 2024
printf "\e[1;34m./pdshow 99991010\e[0m\n"
./pdshow 99991010 ## Test non-existent date

## test pdremove
printf "\n\e[1;31mTesting pdremove\e[0m\n"
printf "\e[1;34m./pdremove today\e[0m\n"
./pdremove today ## Today
printf "\e[1;34m./pdremove 20240401\e[0m\n"
./pdremove 20240401 ## April 1st, 2024
printf "\e[1;34m./pdremove 99991010\e[0m\n"
./pdremove 99991010 ## Test non-existent date
printf "\e[1;34m./pdlist\e[0m\n"
./pdlist ## List the remaining entries after removal

## fancy redirection
printf "\n\e[1;31mTesting fancy redirection\e[0m\n"
printf "\e[1;34m./pdshow 19111010 2> /dev/null | ./pdadd 19190810\e[0m\n"
./pdshow 19111010 2> /dev/null | ./pdadd 19190810
printf "\e[1;34m./pdlist\e[0m\n"
./pdlist ## List the entries after fancy redirection
printf "\e[1;34m./pdshow 19190810\e[0m\n"
./pdshow 19190810 ## Show the entry added by fancy redirection