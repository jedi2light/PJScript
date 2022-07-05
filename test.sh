#!/usr/bin/env bash

# This script helps with testing by comparing a PJScript behaviour to the Node.js one

if [ -z $1 ]; then echo "E: No project path were given"; exit 1; fi
if [ ! -d $1 ]; then echo "E: Can not locate a project"; exit 1; fi

RESULT="${1}/generated/pjs-vs-node.diff"  # set path to a diff file

diff <(./pjs.sh $1 | sed -e '1,3d' -e 's/ $//g') <(node $1/startup.tjs) > "${RESULT}"

if [ -n "$(cat ${RESULT})" ]; then echo "$1: different output, see: '${RESULT}'"; fi

if [ "${KOMPARE}" == "1" ]; then kompare ${RESULT}; fi # optionally view with Kompare
