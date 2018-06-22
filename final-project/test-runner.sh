#!/bin/bash
# Automated Test Runner

for number in {1..100}
do
./dynmem-threading "$number " 10
done
exit 0

