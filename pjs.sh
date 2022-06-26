#!/usr/bin/env bash

# Script which is useful for debugging (or for the new users) :^)

if [ -z $1 ]; then echo "No project path were given!"; exit 1; fi

if [ ! -d $1 ]; then echo "Can not locate a project!"; exit 1; fi

make runtime && ./pjs.py --project $1 && "./$1/$(basename $1).sh"