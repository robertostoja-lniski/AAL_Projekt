#!/bin/bash

cd ..
rm visualisation/time_raport.csv
for i in {0..$1}
do
   echo "testing/test$i.txt"
   ./bin/a.out "testing/test$i.txt"
done