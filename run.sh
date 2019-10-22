#!/usr/bin/env bash
make
EXE=./ksticks.filler
#EXE="python3 proxy_to_file.py"
EXE2=./ksticks.filler
#cp $EXE $EXE2
./resources/filler_vm -p1 "$EXE" -p2 "$EXE2" -f resources/maps/map01 # 2> stderr.txt
echo "------------------stderr.txt-----------------------------"
tail stderr.txt
