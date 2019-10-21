#!/usr/bin/env bash
make
./resources/filler_vm -p1 ./ksticks.filler -p2 cat -f resources/maps/map00 2> stderr.txt
echo "------------------stderr.txt-----------------------------"
cat stderr.txt
