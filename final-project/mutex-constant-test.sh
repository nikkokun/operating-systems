#!/bin/bash
# Automated Test Runner

for number in {1..100}
do
./mutex-constant "$number " 1000
done
exit 0