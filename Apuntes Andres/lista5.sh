#!/bin/bash

# Cogemos N procesos
N="$1"
# Cogemos la lista de ps con su pid
PROCESOS=$(ps --no-headers -eo pid,comm | tail -n $N)
echo "$PROCESOS"

