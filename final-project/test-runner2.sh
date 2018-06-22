#!/bin/bash
# Automated Test Runner

for number in {1..100}
do
./old-threading "$number " 100
done
exit 0