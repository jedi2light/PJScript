#!/usr/bin/env bash

# Script which is useful for debugging (or for the new-comers). :^)
set -e  # if something went wrong, do not continue, stop it instead

if [ -z $1 ]; then echo "E: No project path were given"; exit 1; fi
if [ ! -d $1 ]; then echo "E: Can not locate a project"; exit 1; fi

echo "[1/3]: [Building PJScript runtime]" && make runtime>/dev/null
echo "[2/3]: [Building project]"&&./pjs.py --buildproj $1>/dev/null
echo "[3/3]: [Executing a built project]"&&"./$1/$(basename $1).sh"
