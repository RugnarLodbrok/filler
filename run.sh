#!/usr/bin/env bash
make
EXE=./ksticks.filler
EXE2=./ksticks2.filler
#cp $EXE $EXE2
./resources/filler_vm -p1 $EXE -p2 $EXE2 -f resources/maps/map01 2> stderr.txt
echo "------------------stderr.txt-----------------------------"
tail stderr.txt
