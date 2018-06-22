#!/bin/bash
# Automated Test Runner

for number in {1..100}
do
./dynmem-threading-real "$number " 1000
done
exit 0

