#!/bin/bash
for ((i = 1; i <= 10; i++))
do
	./Maze -r 5 -c 4
	sleep 1
done
