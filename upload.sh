#!/bin/bash

BOARD=

if [[ $# -eq 1 ]]; then
	if [[ $1 == "pico_w" ]]; then
		BOARD=$1
	else
		echo "Only pico_w board other than pico is allowed." 1>&2
		exit 2
	fi
fi

cmake ..
make main
sudo mount -o uid=1000 /dev/sda1 /mnt
if [[ $? -ne 0 ]]; then
	echo "Mounting didn't succeed." 1>&2
	exit 1
fi
cp main.uf2 /mnt
sudo umout /mnt
