#!/bin/sh
#parameters:	1 - magazine size
#		2 - producers number
#		3 - consumers number
#		4 - a (min produce_count)
#		5 - b (max produce_count)
#		6 - c (min take_count)
#		7 - d (max take_count)
#		8 - n 

echo "Number of producers: $2 Number of consumers: $3 Magazine size: $1"
rm buffer.txt
rm fulllog.txt
echo "0" >> buffer.txt

i=$2
while `expr $i != 0`
do
./producer $1 $8 $4 $5 $i &
i=`expr $i - 1`
don

i=$3
while `expr $i != 0`
do
./consumer $1 $8 $6 $7 $i &
i=`expr $i - 1`
done
