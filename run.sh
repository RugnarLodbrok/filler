#!/usr/bin/env bash
make
EXE=./ksticks.filler
#EXE2=./ksticks.filler
#EXE2=./resources/players/abanlin.filler #ez
#EXE2=./resources/players/carli.filler  #ez
#EXE2=./resources/players/champely.filler #not working
#EXE2=./resources/players/grati.filler #ez
#EXE2=./resources/players/hcao.filler #ez
EXE2=./resources/players/superjeannot.filler  #ez
./resources/filler_vm -p1 "$EXE" -p2 "$EXE2" -f resources/maps/map01
